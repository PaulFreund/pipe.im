//======================================================================================================================

Ext.define('PipeUI.view.BaseController', {
	extend: 'Ext.app.ViewController',

	config: {
		listen: {
			global: {
				connection_session: 'onSession',
				connection_disconnected: 'onDisconnected',
				connection_message: 'onMessage',
				browser_service_selected: 'onServiceSelected',
				server_message: 'onServerMessage'
			}
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
		if(!node || !node.data || !node.data.info) { return null; }
		return node.data.info;
	}
});

//======================================================================================================================
