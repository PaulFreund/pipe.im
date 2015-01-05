//======================================================================================================================
/*
	Copyright (c) since 2015 - Paul Freund (freund.paul@lvl3.org)
	
	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:
	
	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/
//======================================================================================================================

Ext.define('PipeUI.controller.Connection', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.app.Controller',

	config: {
		listen: {
			global: {
				connection_connect: 'connect',
				connection_send: 'send',
			}
		}
	},

	//------------------------------------------------------------------------------------------------------------------
	// Events

	onLaunch: function () {
		this.checkAuthenticated();

		Ext.interval(function () {
			try {
				this.checkAuthenticated();
			}
			catch(e) {}
		}, 5000, this, []);
	},

	onUnauthenticated: function () {
		if(this.loginWindow) { return; }

		this.loginWindow = Ext.create('PipeUI.view.dialog.Login', {
			autoShow: true,
			listeners: {
				scope: this,
				loginComplete: function () {
					this.checkAuthenticated();
				}
			}
		});
	},

	onAuthenticated: function () {
		if(this.loginWindow) {
			this.loginWindow.destroy();
			this.loginWindow = undefined;
		}

		// If we don't have a socket or the socket is closed, try connecting
		if(!this.socket || this.socket.readyState === WebSocket.CLOSED) {
			this.connect();
		}
	},

	onConnected: function () {
		Ext.log({ level: 'debug' }, '[Connection::onConnected]');
		this.sessionRequested = true;
		this.socket.send(JSON.stringify({ request: 'login', admin: false, shell: false, authToken: Ext.util.Cookies.get('authToken') }));
		Ext.GlobalEvents.fireEvent('connection_connected');
	},

	onConnectionError: function () {
		Ext.log({ level: 'debug' }, '[Connection::onConnectionError]');
		Ext.GlobalEvents.fireEvent('connection_connectionError');
		this.onDisconnected(0, 'onConnectionError', false);
	},

	onDisconnected: function (code, reason, wasClean) {
		Ext.log({ level: 'debug' }, '[Connection::onDisconnected] ' + reason);
		Ext.GlobalEvents.fireEvent('connection_disconnected');
		this.cleanup()
	},

	onMessage: function (message) {
		var messageText = message.data.toString();
		//Ext.log({ level: 'debug' }, '[Connection::onMessage] ' + messageText);
		var data = JSON.parse(messageText);
		if(this.sessionRequested) {
			if (data.success && data.session !== undefined) {
				Ext.log({ level: 'debug' }, '[Connection::onMessage] Got session: ' + data.session);
				this.session = data.session;
				this.sessionRequested = false;
				Ext.GlobalEvents.fireEvent('connection_session', this.session);
				return;
			}
		}

		Ext.GlobalEvents.fireEvent('connection_message', data);
	},

	//------------------------------------------------------------------------------------------------------------------
	// Methods

	checkAuthenticated: function () {
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

	connect: function () {
		var myself = this;
		this.socket = new WebSocket('ws://' + window.location.host + window.location.pathname);
		this.socket.onopen = function () { myself.onConnected.call(myself); }
		this.socket.onerror = function () { myself.onConnectionError.call(myself); }
		this.socket.onclose = function (code, reason, wasClean) { myself.onDisconnected.call(myself, code, reason, wasClean); }
		this.socket.onmessage = function (message) { myself.onMessage.call(myself, message); }
	},

	send: function (msg) {
		if(!this.socket || this.socket.readyState !== WebSocket.OPEN) {
			Ext.GlobalEvents.fireEvent('connection_error', 'Sending failed');
			return;
		}

		msg.timestamp = Math.round(new Date().getTime() / 1000);
		msg.ref = this.session;
		this.socket.send(JSON.stringify(msg));
		Ext.GlobalEvents.fireEvent('connection_sent', msg);
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
