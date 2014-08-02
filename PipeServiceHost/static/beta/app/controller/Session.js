Ext.define('PipeUI.controller.Session', {
	extend: 'Ext.app.Controller',

	requires: [
		'PipeUI.view.login.LoginWindow'
	],

	init: function () {
		this.application.on('isAuthenticated', this.isAuthenticated);
	},

	onLaunch: function () {
		this.isAuthenticated();
	},

	isAuthenticated: function() {
		Ext.log({ level: 'debug' }, '[Session::isAuthenticated]');
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
		Ext.log({ level: 'debug' }, '[Session::onUnauthenticated]');
		this.application.fireEvent('unauthenticated');
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
		Ext.log({ level: 'debug' }, '[Session::onAuthenticated]');
		if (this.loginWindow) { this.loginWindow.destroy(); }
		this.application.fireEvent('authenticated');
	},
});
