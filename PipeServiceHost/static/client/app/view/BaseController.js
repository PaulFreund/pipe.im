//======================================================================================================================

Ext.define('PipeUI.view.BaseController', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.app.ViewController',
	alias: 'controller.baseController',

	//------------------------------------------------------------------------------------------------------------------

	init: function () {
		this.register('connection_session', this.onSession);
		this.register('connection_disconnected', this.onDisconnected);
		this.register('connection_message', this.onMessage);
		this.register('browser_service_selected', this.onServiceSelected);
		this.register('server_message', this.onSession);
		this.register('connection_session', this.onServerMessage);
		if(this.onInit) { this.onInit(); }

		this.view.on('beforedestroy', this.unregister, this);

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
		for(var handler in this.registered) {
			if(!this.registered.hasOwnProperty(handler)) { continue; }
			Ext.un(handler, this.registered[handler], this);
		}
	},

	send: function (data) {
		Ext.GlobalEvents.fireEvent('connection_send', data);
	},

	getServices: function () {
		var store = Ext.StoreManager.lookup('Services');
		if(!store) { return null; }

		return store.getRoot();
	},

	getService: function (address) {
		var root = this.getServices();
		if(!root) { return null; }

		var node = root.findChild('address', address, true);
		if(!node || !node.data || !node.data.address) { return null; }
		return node;
	},


	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================
