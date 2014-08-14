//======================================================================================================================

Ext.define('PipeUI.view.conversation.server', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'PipeUI.view.conversation.BaseView',
	xtype: 'pipe-conversation-server',

	//------------------------------------------------------------------------------------------------------------------
	
	controller: {
		onSession: function () {
			this.addMessage('Got Session');
		},

		onDisconnected: function () {
			this.addMessage('Disconnected');
		}
	}

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================
