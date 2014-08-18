//======================================================================================================================

Ext.define('PipeUI.view.ConversationHost', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.tab.Panel',
	xtype: 'pipe-conversationhost',

	//------------------------------------------------------------------------------------------------------------------

	defaults: {
		closable: true
	},

	items: [
		{
			xtype: 'pipe-conversation-server',
			closable: false,
			tabConfig: {
				title: 'Server',
				tooltip: 'All unassigned messages'
			},
			address: 'pipe'
		}
	],

	//------------------------------------------------------------------------------------------------------------------

	controller: {
		type: 'baseController',

		onServiceSelected: function (address) {
			if(!address) { return; }
			this.updateConversation(address, true);
		},

		//--------------------------------------------------------------------------------------------------------------

		pending: {},

		//--------------------------------------------------------------------------------------------------------------

		onSession: function (session) {
			this.pending = {};
		},

		onDisconnected: function () {
			var view = this.getView();
			if(!view.items || !view.items.items || view.items.items.length > 0) {
				Ext.iterate(view.items.items, function (item) {
					if(item.address !== 'pipe' && item.closable)
						item.close();
				}, this);
			}
			this.pending = {};
		},

		onMessage: function (msg) {
			this.updateConversation(msg.address, false, msg);
		},

		onServiceUpdate: function (address, node) {
			var conv = this.getConversation(address);
			if(address !== 'pipe' && conv && conv.tab) {
				conv.tab.setText(node.data.state.name);
				conv.tab.setTooltip(node.data.state.description);
			}

			if(this.pending[address] && this.pending[address].messages.length) {
				this.updateConversation(address, false);
			}
		},

		onServiceRemoved: function(address) {
			var conv = this.getConversation(address);
			if(conv) { conv.close(); }
		},

		//--------------------------------------------------------------------------------------------------------------

		updateConversation: function(address, activate, msg) {
			// Add to pending list
			if(!this.pending[address]) {
				this.pending[address] = { activate: activate, messages: [] };
			}

			if(msg) { this.pending[address].messages.push(msg); }
			this.pending[address].activate = activate;

			// Check if conversation is already open
			var conv = this.getConversation(address);

			if(!conv) {
				// If service exists
				var service = this.getService(address);
				if(!service || !service.data) { return; }

				var create = true;
				if(!activate && (msg || this.pending[address].messages.length)) {
					// Check if the conversation type wants to be created
					var convType = PipeUI.view.conversation[service.data.typeName];
					if(convType && convType.constants) {
						var constants = convType.constants;

						// Get default for creation
						create = (constants.defaults && constants.defaults.creates !== undefined) ? constants.defaults.creates : false;

						// Check for every message type
						Ext.iterate(this.pending[address].messages, function(msg) {
							if(!constants.types[msg.message]) { return; }

							if(constants.types[msg.message].creates === true) {
								create = true;
								return false;
							}	
						}, this);
					}
				}

				if(create) {
					// Creat conversation if requested
					conv = this.createConversation(service.data);

					// Add messages if any
					if(conv && conv.controller) {
						Ext.iterate(this.pending[address].messages, function(msg) {
							conv.controller.onMessage(msg);
						}, this);
					}
				}

				// Delete pending messages
				this.pending[address].messages = [];
			}

			// Activate conversation if requested
			if(conv && this.pending[address].activate) { this.getView().setActiveTab(conv); }
			this.pending[address].activate = false;
		},

		getConversation: function (address) {
			var view = this.getView();
			return view.items.findBy(function (item, key) {
				return item.address == address;
			}, this);
		},

		createConversation: function (service) {
			// Get xtype
			var viewType = 'default';
			if(service.typeName && service.typeName.length > 0 && PipeUI.view.conversation[service.typeName]) {
				viewType = service.typeName;
			}

			// Create new conversation
			if(!service.state.name) { debugger; }
			return this.getView().add(new PipeUI.view.conversation[viewType]({
				tabConfig: {
					title: service.state.name,
					tooltip: service.state.description
				},
				address: service.address
			}));
		}
	}

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================
