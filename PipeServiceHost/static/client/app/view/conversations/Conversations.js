//======================================================================================================================

Ext.define('PipeUI.view.conversations.Conversations', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.tab.Panel',
	xtype: 'pipe-conversations-conversations',

	//------------------------------------------------------------------------------------------------------------------

	controller: 'ConversationsController',

	//------------------------------------------------------------------------------------------------------------------

	defaults: {
		closable: true
	},

	items: [{
		title: 'Active Tab',
		html: "Hi"
	}, {
		title: 'Inactive Tab',
		html: "There"
	}, {
		title: 'Disabled Tab',
		disabled: true
	}],

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================

Ext.define('PipeUI.view.conversations.ConversationsController', {
	extend: 'Ext.app.ViewController',
	alias: 'controller.ConversationsController',

	config: {
		listen: {
			global: {
				session: 'onSession',
				disconnected: 'onDisconnected',
				message: 'onMessage',
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
		Ext.GlobalEvents.fireEvent('send', data);
	}
});

//======================================================================================================================
