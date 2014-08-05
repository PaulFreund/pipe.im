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
		var conv = this.ensureConversation(address);
		if(!conv) { return; }

		var view = this.getView();
		view.setActiveTab(conv);
	},

	onSession: function (session) {
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
	},

	onMessage: function (msg) {
		switch(msg.message) {
			case 'children':
			case 'node_added':
				break;

			case 'info':
				var conv = this.getConversation(msg.address);
				if(!conv) { return; }
				debugger;
				conv.title = msg.data.instance_name;
				conv.tooltip = msg.data.instance_description;
				break;

			case 'node_removed':
				var conv = this.getConversation(info.address);
				if(conv) { conv.close(); }
				break;

			// TODO: this is a test setting
			//default:
			case 'message':
				var view = this.getView();
				var conv = this.ensureConversation(msg.address, msg);
				if(!conv) {
					Ext.GlobalEvents.fireEvent('server_message', msg);
					return;
				}
				// TODO: Temporary
				conv.tab.setGlyph(99);

				break;

			default:
				Ext.GlobalEvents.fireEvent('server_message', msg);
				// TODO: Find something to highlight the tab
				//view.setActiveTab(conversation);
		}
	},

	getConversation: function (address) {
		var view = this.getView();
		return view.items.findBy(function (item, key) {
			return item.address == address;
		}, this);
	},

	ensureConversation: function (address, initialMessage) {
		// Check if conversation exists
		var conv = this.getConversation(address);
		if(conv) { return conv; }

		// Get Service
		var svc = this.getService(address);
		if(!svc) { return null; }

		// Get xtype
		var viewType = 'default'; 
		if(svc.type_name && svc.type_name.length > 0 && PipeUI.view.conversation[svc.type_name]) {
			viewType = svc.type_name;
		}

		var newView = new PipeUI.view.conversation[viewType]({
			tabConfig: {
				title: svc.instance_name,
				tooltip: svc.instance_description
			},
			address: svc.address,
			initialMessage: initialMessage
		});

		// Create new conversation
		return this.getView().add(newView);
	},

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================
