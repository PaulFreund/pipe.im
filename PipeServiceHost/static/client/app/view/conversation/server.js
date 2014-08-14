//======================================================================================================================

Ext.define('PipeUI.view.conversation.server', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'PipeUI.view.conversation.BaseView',
	xtype: 'pipe-conversation-server',

	//------------------------------------------------------------------------------------------------------------------
	
	controller: {
		onSession: function () {
			this.onReceived('Got Session');
		},

		onDisconnected: function () {
			this.onReceived('Disconnected');
			//Ext.GlobalEvents.fireEvent('connection_connect');
		},

		onReceived: function (msg) {
			this.addMessage(JSON.stringify(msg));
		},

		onServerMessage: function (msg) {
			this.onReceived(msg);
		}
	}

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================
