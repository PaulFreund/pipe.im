//======================================================================================================================

Ext.define('PipeUI.view.status.Status', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.toolbar.Toolbar',
	xtype: 'pipe-status-status',

	//------------------------------------------------------------------------------------------------------------------

	controller: 'StatusController',

	//------------------------------------------------------------------------------------------------------------------

	style: 'background-color: #333;'

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================

Ext.define('PipeUI.view.status.StatusController', {
	extend: 'Ext.app.ViewController',
	alias: 'controller.StatusController',

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
	},

	send: function (data) {
		Ext.GlobalEvents.fireEvent('connection_send', data);
	}
});
//======================================================================================================================
