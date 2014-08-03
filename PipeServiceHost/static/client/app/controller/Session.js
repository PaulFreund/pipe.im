//======================================================================================================================

Ext.define('PipeUI.controller.Session', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.app.Controller',

	views: [
		'status.Status',
		'browser.Browser',
		'conversations.Conversations'
	],

	//------------------------------------------------------------------------------------------------------------------

	config: {
		listen: {
			global: {
				session: 'onSession',
				disconnected: 'onDisconnected',
				message: 'onMessage',
			}
		}
	},

	//------------------------------------------------------------------------------------------------------------------

	onSession: function (session) {
		this.session = session;
	},

	onDisconnected: function () {
		this.session = undefined;
	},

	onMessage: function (msg) {
	},

	//------------------------------------------------------------------------------------------------------------------

	send: function (data) {
		Ext.GlobalEvents.fireEvent('send', data);
	},
});

//======================================================================================================================
