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

	onSession: function (session) {
		this.session = session;
	},

	onDisconnected: function () {
		this.session = undefined;
	},

	onMessage: function (msg) {
		switch(msg.message) {
			// Ignore these
			case 'children':
			case 'node_added':
			case 'node_info_updated':
			case 'info':
				break;

			case 'node_removed':
				//var conversation = this.findTab(info.address);
				//if(conversation) { conversation.close(); }
				//debugger;
				break;
		}
		var view = this.getView();
		//debugger;
	},

	send: function (data) {
		Ext.GlobalEvents.fireEvent('connection_send', data);
	}
});

//======================================================================================================================
