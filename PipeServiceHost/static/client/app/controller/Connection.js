//======================================================================================================================

Ext.define('PipeUI.controller.Connection', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.app.Controller',

	requires: [
		'PipeUI.view.login.LoginWindow'
	],

	config: {
		listen: {
			global: {
				connect: 'connect',
				disconnect: 'disconnect',
				send: 'send',
			}
		}
	},

	//------------------------------------------------------------------------------------------------------------------
	// Events

	onLaunch: function () {
		this.isAuthenticated();
	},

	onUnauthenticated: function () {
		Ext.log({ level: 'debug' }, '[Connection::onUnauthenticated]');
		Ext.GlobalEvents.fireEvent('unauthenticated');
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
		Ext.GlobalEvents.fireEvent('authenticated');
		this.connect();
	},

	onConnected: function () {
		Ext.log({ level: 'debug' }, '[Connection::onConnected]');
		this.sessionRequested = true;
		this.socket.send(JSON.stringify({ request: 'login', admin: false, shell: false, authToken: Ext.util.Cookies.get('authToken') }));
		Ext.GlobalEvents.fireEvent('connected');
	},

	onConnectionError: function () {
		Ext.log({ level: 'debug' }, '[Connection::onConnectionError]');
		Ext.GlobalEvents.fireEvent('connectionError');
		this.onDisconnected();
	},

	onDisconnected: function (code, reason, wasClean) {
		Ext.log({ level: 'debug' }, '[Connection::onDisconnected] ' + reason);
		Ext.GlobalEvents.fireEvent('disconnected');
		this.cleanup()
	},

	onMessage: function (message) {
		var messageText = message.data.toString();
		//Ext.log({ level: 'debug' }, '[Connection::onMessage] ' + messageText);
		var data = JSON.parse(messageText);
		if (this.sessionRequested) {
			if (data.success && data.session !== undefined) {
				Ext.log({ level: 'debug' }, '[Connection::onMessage] Got session: ' + data.session);
				this.session = data.session;
				this.sessionRequested = false;
				Ext.GlobalEvents.fireEvent('session', this.session);
				return;
			}
		}

		Ext.GlobalEvents.fireEvent('message', data);
	},

	//------------------------------------------------------------------------------------------------------------------
	// Methods

	isAuthenticated: function () {
		Ext.log({ level: 'debug' }, '[Connection::isAuthenticated]');
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

	disconnect: function () {
		Ext.log({ level: 'debug' }, '[Connection::disconnect]');
		this.onDisconnected();
	},

	connect: function () {
		var myself = this;
		this.socket = new WebSocket('ws://' + window.location.host + window.location.pathname);
		this.socket.onopen = function () { myself.onConnected.call(myself); }
		this.socket.onerror = function () { myself.onConnectionError.call(myself); }
		this.socket.onclose = function (code, reason, wasClean) { myself.onDisconnected.call(myself, code, reason, wasClean); }
		this.socket.onmessage = function (message) { myself.onMessage.call(myself, message); }
	},

	send: function(msg) {
		if(!this.socket || this.socket.readyState !== WebSocket.OPEN) {
			Ext.GlobalEvents.fireEvent('error', 'Sending failed');
			return;
		}

		msg.ref = this.session;
		this.socket.send(JSON.stringify(msg));
	},

	cleanup: function () {
		if(this.socket !== undefined) {
			try {
				this.socket.close();
			}
			catch (e) { }
		}

		this.session = undefined;
		this.sessionRequested = false;
		this.socket = undefined;
	}

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================