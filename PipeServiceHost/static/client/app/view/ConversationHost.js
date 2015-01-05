//======================================================================================================================
/*
	Copyright (c) since 2015 - Paul Freund (freund.paul@lvl3.org)
	
	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:
	
	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/
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
			if((resItems = ph.res(this, 'view.items.items')) !== null) {
				Ext.each(resItems, function (item) {
					if(item && item.address && item.address !== 'pipe' && item.closable)
						item.close();
				}, this, true);
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
					if((resConst = ph.res(PipeUI, 'view.conversation.' + service.data.typeName + '.constants.messages')) !== null) {

						// Get default
						if((resDefault = ph.res(resConst, 'defaults.creates')) !== null) {
							create = resDefault;
						}

						// Check for every message type
						Ext.iterate(this.pending[address].messages, function (msg) {
							if((resType = ph.res(resConst, msg.message + '.creates')) !== null) {
								if(resType) {
									create = true;
									return false;
								}
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
