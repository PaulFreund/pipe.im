//======================================================================================================================

Ext.define('PipeUI.view.Status', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.toolbar.Toolbar',
	xtype: 'pipe-status',


	//------------------------------------------------------------------------------------------------------------------

	style: 'background-color: #333;',

	//------------------------------------------------------------------------------------------------------------------

	controller: Ext.create('PipeUI.view.BaseController', {
		onSession: function (session) {
			this.session = session;
		},

		onDisconnected: function () {
			this.session = undefined;
		},

		onMessage: function (msg) {
		},
	})

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================