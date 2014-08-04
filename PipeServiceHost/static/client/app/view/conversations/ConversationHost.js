//======================================================================================================================

Ext.define('PipeUI.view.conversations.ConversationHost', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.tab.Panel',
	xtype: 'pipe-conversation-conversation-host',

	//------------------------------------------------------------------------------------------------------------------

	controller: 'ConversationHostController',

	//------------------------------------------------------------------------------------------------------------------

	defaults: {
		closable: true
	}

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================

Ext.define('PipeUI.view.conversations.ConversationHostController', {
	extend: 'Ext.app.ViewController',
	alias: 'controller.ConversationHostController',

	requires: [
		'PipeUI.view.conversations.Conversation' 
	],

	config: {
		listen: {
			global: {
				connection_session: 'onSession',
				connection_disconnected: 'onDisconnected',
				connection_message: 'onMessage',
				browser_service_selected: 'onServiceSelected'
			}
		}
	},

	onServiceSelected: function (info) {
		if(!info.address) { return; }

		var view = this.getView();
		var conversation = this.findTab(info.address);

		if(!conversation) {
			conversation = view.add({
				xtype: 'pipe-conversations-conversation',
				tabConfig: {
					title: info.instance_name,
					tooltip: info.instance_description
				},
				address: info.address
			});
		}

		view.setActiveTab(conversation);
	},

	onSession: function (session) {
		this.session = session;
	},

	onDisconnected: function () {
		var view = this.getView();
		if(!view.items || view.items.length > 0)
		Ext.Array.forEach(view.items, function (item) {
			item.close();
		}, this);
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
				var conversation = this.findTab(info.address);
				if(conversation) { conversation.close(); }
				debugger;
				break;

			default:
				var conversation = this.findTab(msg.address);
				if(!conversation) {

					var node = this.findNode(msg.address);
					if(!node) { return; }

					var view = this.getView();
					conversation = view.add({
						xtype: 'pipe-conversations-conversation',
						tabConfig: {
							title: node.data.info.instance_name,
							tooltip: node.data.info.instance_description
						},
						address: node.data.info.address
					});

					// TODO: Send Conversation the initial message
				}

				// TODO: Find something to highlight the tab
				//view.setActiveTab(conversation);

				break;
		}
	},

	send: function (data) {
		Ext.GlobalEvents.fireEvent('connection_send', data);
	},

	findTab: function (address) {
		var view = this.getView();
		return view.items.findBy(function (item, key) {
			return item.address == address;
		}, this);
	},

	findNode: function (address) {
		var store = Ext.StoreManager.lookup('Services');
		if(!store) { return null; }

		var root = store.getRoot();
		if(!root) { return null; }

		return root.findChild('address', address, true);
	}
});

//======================================================================================================================
