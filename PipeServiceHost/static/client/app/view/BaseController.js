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

Ext.define('PipeUI.view.BaseController', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.app.ViewController',
	alias: 'controller.baseController',

	//------------------------------------------------------------------------------------------------------------------

	init: function () {
		this.register('connection_session', this.on_connection_session);
		this.register('connection_disconnected', this.on_connection_disconnected);
		this.register('connection_message', this.on_connection_message);
		this.register('connection_sent', this.on_connection_sent);

		this.register('service_update', this.onServiceUpdate);
		this.register('service_removed', this.onServiceRemoved);

		this.register('browser_service_selected', this.onServiceSelected);

		if(this.onInit) { this.onInit(); }

		this.view.on('beforedestroy', this.unregister, this);

	},

	//------------------------------------------------------------------------------------------------------------------

	on_connection_session: function (session) {
		this.session = session;
		if(this.onSession) { this.onSession(session); }
	},

	on_connection_disconnected: function () {
		this.session = undefined;
		if(this.onDisconnected) { this.onDisconnected(); }
	},

	on_connection_message: function (msg) {
		switch(msg.message) {
			case 'info':
			case 'state':
			case 'state_updated':
			case 'children':
			case 'node_added':
			case 'node_removed':
				break;

			default:
				if(this.onMessage) { this.onMessage(msg); }
				break;
		}
	},

	on_connection_sent: function(msg) {
		switch(msg.command) {
			case 'info':
			case 'command':
			case 'message':
				break;

			default:
				if(this.onSent) { this.onSent(msg); }
				break;
		}
	},

	//------------------------------------------------------------------------------------------------------------------

	registered: {},

	register: function(event, fn) {
		if(fn) {
			Ext.on(event, fn, this);
			this.registered[event] = fn;
		}
	},

	unregister: function () {
		Ext.iterate(this.registered, function (index, handler) {
 			Ext.un(index, handler, this);
		}, this);
	},

	send: function (data) {
		Ext.GlobalEvents.fireEvent('connection_send', data);
	},

	getServices: function () {
		var store = Ext.getStore('Services');
		if(!store) { return null; }

		return store.getRoot();
	},

	getService: function (address) {
		var root = this.getServices();
		if(!root) { return null; }

		var node = root.findChild('address', address, true);
		if(!ph.res(node, 'data.address')) { return null; }
		return node;
	}

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================
