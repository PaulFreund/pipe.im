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
	}

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================

Ext.define('PipeUI.view.ConversationHostController', {
	extend: 'PipeUI.view.ViewControllerBase',
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
				item.close();
			}, this);
		}
		this.session = undefined;
	},

	onMessage: function (msg) {
		switch(msg.message) {
			case 'children':
			case 'node_added':
			case 'node_info_updated':
			case 'info':
				break;

			case 'node_removed':
				var conv = this.getConversation(info.address);
				if(conv) { conv.close(); }
				break;

			default:
				var view = this.getView();
				var conv = this.ensureConversation(msg.address, msg);
				if(!conv) { return; }

				// TODO: Find something to highlight the tab
				//view.setActiveTab(conversation);

				break;
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
		if(!svc) {
			// TODO: What to do in this case, we don't know the type of the node yet and thus can't create the correct one
			debugger;
			return null;
		}

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
