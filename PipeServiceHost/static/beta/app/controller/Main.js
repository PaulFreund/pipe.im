Ext.define('PipeUI.controller.Main', {
	extend: 'Ext.app.Controller',

	requires: [
		'PipeUI.view.main.Main',
		'PipeUI.view.login.LoginWindow'
	],

	onLaunch: function () {
		this.isAuthenticated();
	},

	isAuthenticated: function() {
		var self = this;
		Ext.Ajax.request({
			url: '/rest/authenticated',
			disableCaching: false,
			success: function (response) {
				if (response.responseText === 'true')
					self.onAuthenticated();
				else
					self.onUnauthenticated();
			},
			failure: function (response, opts) {
				self.onUnauthenticated();
			}
		});
	},

	onUnauthenticated: function () {
		if (this.viewport) { this.viewport.destroy(); }

		this.loginWindow = new PipeUI.view.login.LoginWindow({
			autoShow: true,
			listeners: {
				scope: this,
				loginComplete: function () {
					this.isAuthenticated();
				}
			}
		});
	},

	onAuthenticated: function () {
		if (this.loginWindow) { this.loginWindow.destroy(); }
		this.viewport = new PipeUI.view.main.Main();
	},
});
