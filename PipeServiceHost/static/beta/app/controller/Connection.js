Ext.define('PipeUI.controller.Connection', {
	extend: 'Ext.app.Controller',

	views: [
		'main.Status',
		'main.Browser',
		'main.Conversations'
	],

	init: function () {
		this.application.on('authenticated', this.connect, this);
		this.application.on('unauthenticated', this.disconnect, this);
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

	onConnected: function() {
		Ext.log({ level: 'debug' }, '[Connection::onConnected]');	
		this.socket.send(JSON.stringify({request: 'login', admin: false, shell: false, authToken: Ext.util.Cookies.get('authToken')}));
	},

	onConnectionError: function () {
		Ext.log({ level: 'debug' }, '[Connection::onConnectionError]');
		this.onDisconnected();
	},

	onDisconnected: function (code, reason, wasClean) {
		Ext.log({ level: 'debug' }, '[Connection::onDisconnected] ' + reason);
		try {
			this.socket.close();
		}
		catch (e) {}
		this.socket = null;
	},

	onMessage: function (message) {
		Ext.log({ level: 'debug' }, '[Connection::onMessage] ' + message.data.toString());
	}
});


