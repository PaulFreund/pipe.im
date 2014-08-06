//======================================================================================================================

Ext.define('PipeUI.view.ConversationHost', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.tab.Panel',
	xtype: 'pipe-conversationhost',

	//------------------------------------------------------------------------------------------------------------------

	controller: 'ConversationHostController',

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
	]

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================

Ext.define('PipeUI.view.ConversationHostController', {
	extend: 'PipeUI.view.BaseController',
	alias: 'controller.ConversationHostController',

	onServiceSelected: function (address) {
		if(!address) { return; }
		this.openConversation(address, true);
	},

	pending: {},

	onSession: function (session) {
		this.pending = {};
		this.session = session;
	},

	onDisconnected: function () {
		var view = this.getView();
		if(!view.items || view.items.length > 0) {
			Ext.Array.forEach(view.items, function (item) {
				if(item.closable)
					item.close();
			}, this);
		}
		this.session = undefined;
		this.pending = {};
	},

	onMessage: function (msg) {
		switch(msg.message) {
			case 'children':
			case 'node_added':
				break;

			case 'info':
				// open if pending
				if(this.pending[msg.address]) {
					this.openConversation(msg.address, false, msg);
					break;
				}
				break;

			case 'node_removed':
				var conv = this.getConversation(info.address);
				if(conv) { conv.close(); }
				break;

			// Dispatch messages
			default:
				this.openConversation(msg.address, false, msg);
				break;

		}
	},

	getConversation: function (address) {
		var view = this.getView();
		return view.items.findBy(function (item, key) {
			return item.address == address;
		}, this);
	},

	openConversation: function (address, activate, message) {
		// Get probably existing conversation
		var conv = this.getConversation(address);

		// Try to create new
		if(!conv) {
			// Get service for address if possible, add to pendig if not
			var service = this.getService(address);
			if(!service) {
				if(!this.pending[address]) {
					this.pending[address] = {
						activate: activate,
						messages: [message]
					};
				}
				else {
					this.pending[address].messages.push(message);
				}

				return;
			}
			else {
				// Create conversation with service
				conv = this.createConversation(service);
				if(!conv) { debugger; }
			}

			// Messages to be added to new view
			var messages = message ? [message] : [];

			// Add pending information
			if(this.pending[address]) {
				if(this.pending[address].activate) { activate = true; }
				if(this.pending[address].messages) { messages = messages.concat(this.pending[address].messages); }
				delete this.pending[address];
			}

			// Add messages if any
			var controller = conv.getController();
			if(controller) {
				for(var idx in messages) { controller.onMessage(messages[idx]); }
			}
		}

		// Activate if requested
		if(activate) { this.getView().setActiveTab(conv);}
	},

	createConversation: function(service) {
		// Get xtype
		var viewType = 'default';
		if(service.type_name && service.type_name.length > 0 && PipeUI.view.conversation[service.type_name]) {
			viewType = service.type_name;
		}

		// Create new conversation
		return this.getView().add(new PipeUI.view.conversation[viewType]({
			tabConfig: {
				title: service.instance_name,
				tooltip: service.instance_description
			},
			address: service.address
		}));
	}

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================
