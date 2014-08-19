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

		this.register('connection_error', this.onConnectionError);

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

	registered: [],

	register: function(event, fn) {
		if(fn) {
			Ext.on(event, fn, this);
			this.registered[event] = fn;
		}
	},

	unregister: function () {
		Ext.iterate(this.registered, function(handler, index) {
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
