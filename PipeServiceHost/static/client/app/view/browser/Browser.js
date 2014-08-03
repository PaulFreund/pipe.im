//======================================================================================================================

Ext.define('PipeUI.view.browser.Browser', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.tree.Panel',
	xtype: 'pipe-browser-browser',

	//------------------------------------------------------------------------------------------------------------------

	controller: 'BrowserController',
	store: 'Services',

	//------------------------------------------------------------------------------------------------------------------

	title: 'Browser',
	rootVisible: false,

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================

Ext.define('PipeUI.view.browser.BrowserController', {
	extend: 'Ext.app.ViewController',
	alias: 'controller.BrowserController',

	config: {
		listen: {
			global: {
				session: 'onSession',
				disconnected: 'onDisconnected',
				message: 'onMessage',
			}
		}
	},

	onSession: function (session) {
		this.session = session;

		this.send({ address: 'pipe', command: 'children' });
	},

	onDisconnected: function () {
		var store = this.getView().getStore();
		store.removeAll();
		this.session = undefined;
	},

	onMessage: function (msg) {
		if(msg.message === 'children') {
			if(msg.data && msg.data.length > 0) {
				Ext.Array.forEach(msg.data, function (child) {
					var node = this.getServiceNode(child);
					this.send({ address: child, command: 'children' });
					this.send({ address: child, command: 'info' });
				}, this);
			}
		}
		else if(msg.message === 'info') {
			var node = this.getServiceNode(msg.data.address);
			node.set('text', msg.data.instance_name);
			node.set('info', msg.data);
		}
		else if(msg.message === 'node_added') {
			var node = this.getServiceNode(msg.data);
			this.send({ address: msg.data, command: 'info' });
		}
		else if(msg.message === 'node_removed') {
			var node = this.getServiceNode(msg.data);
			// TODO: Debug
			node.erase();
		}
		else if(msg.message === 'node_info_updated') {
			this.send({ address: msg.data, command: 'info' });
		}
	},

	send: function (data) {
		Ext.GlobalEvents.fireEvent('send', data);
	},

	getServiceNode: function (address) {
		var store = this.getView().getStore();
		var root = store.getRoot();
		if(address == 'pipe') { return root; }

		var child = root.findChild('address', address, true);

		if(child != null) { return child; }
		var parent = root;

		// Ensure creation of parents
		var path = address.split('.');
		if(path.length > 1) {
			path.splice(-1, 1);
			parent = this.getServiceNode(path.join('.'));
		}

		if(!parent.data.expandable)
			parent.set('expandable', true);

		// Create new child node
		var newChild = parent.createNode({
			address: address,
			text: address,
			expandable: false,
			info: {}
		});

		parent.appendChild(newChild);
		return newChild;
	}
});

//======================================================================================================================
