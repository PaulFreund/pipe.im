//======================================================================================================================

//======================================================================================================================

Ext.define('PipeUI.view.conversations.Conversation', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.Container',
	xtype: 'pipe-conversations-conversation',

	//------------------------------------------------------------------------------------------------------------------

	controller: 'ConversationController',

	//------------------------------------------------------------------------------------------------------------------


	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================

Ext.define('PipeUI.view.conversations.ConversationController', {
	extend: 'Ext.app.ViewController',
	alias: 'controller.ConversationController',

	config: {
		listen: {
			global: {
				connection_session: 'onSession',
				connection_disconnected: 'onDisconnected',
				connection_message: 'onMessage',
			}
		}
	},

	init: function () {
		var view = this.getView();
		if(view.initialMessage) {
			this.onMessage(view.initialMessage);
			view.initialMessage = null;
		}
	},

	onSession: function (session) {
		this.session = session;
	},

	onDisconnected: function () {
		this.session = undefined;
	},

	onMessage: function (msg) {
		var view = this.getView();
		if(msg.address != view.address) { return; }

		switch(msg.message) {
			case 'children':
			case 'node_added':
			case 'node_info_updated':
			case 'info':
			case 'node_removed':
				break;

			default:
				if(!view.body)
					view.html = JSON.stringify(msg);
				else
					view.body += '<br>' + JSON.stringify(msg);
				break;
		}
	},

	send: function (data) {
		Ext.GlobalEvents.fireEvent('connection_send', data);
	}
});

//======================================================================================================================
