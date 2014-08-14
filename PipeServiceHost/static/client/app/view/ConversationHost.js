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

		pending: {},

		onSession: function (session) {
			this.pending = {};
			this.session = session;
		},

		onDisconnected: function () {
			var view = this.getView();
			if(!view.items || !view.items.items || view.items.items.length > 0) {
				Ext.Array.forEach(view.items.items, function (item) {
					if(item.address !== 'pipe' && item.closable)
						item.close();
				}, this);
			}
			this.session = undefined;
			this.pending = {};
		},

		onMessage: function (msg) {
			switch(msg.message) {
				case 'info':
				case 'children':
				case 'node_added':
					break;

				case 'node_removed':
					var conv = this.getConversation(info.address);
					if(conv) { conv.close(); }
					break;

				default:
					this.updateConversation(msg.address, false, msg);
					break;
			}
		},

		onServiceUpdate: function (address) {
			if(this.pending[address] && this.pending[address].messages.length) {
				this.updateConversation(address, false);
			}
		},

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

				var shouldCreate = true;
				if(!activate && (msg || this.pending[address].messages.length)) {
					// Check if the conversation type wants to be created
					var convType = PipeUI.view.conversation[service.data.typeName];
					if(convType && convType.shouldCreate) {
						shouldCreate = false;
						for(var msg in this.pending[address].messages) {
							if(convType.shouldCreate(this.pending[address].messages[msg].message)) {
								shouldCreate = true;
								break;
							}
						}
					}
				}

				if(shouldCreate) {
					// Creat conversation if requested
					conv = this.createConversation(service.data);

					// Add messages if any
					if(conv && conv.controller) {
						for(var msg in this.pending[address].messages) {
							conv.controller.onMessage(this.pending[address].messages[msg]);
						}
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
