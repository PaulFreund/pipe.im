//======================================================================================================================

Ext.define('PipeUI.controller.Session', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.app.Controller',

	views: [
		'main.Status',
		'main.Browser',
		'main.Conversations'
	],

	stores: ['Services'],

	//------------------------------------------------------------------------------------------------------------------

	init: function () {
		this.application.on('session', this.onSession, this);
		this.application.on('disconnected', this.onDisconnected, this);
		this.application.on('message', this.onMessage, this);
	},

	//------------------------------------------------------------------------------------------------------------------

	onSession: function (session) {
		this.session = session;

		this.send({ address: 'pipe', command: 'children' });
	},

	onDisconnected: function () {
		var store = this.getServicesStore();
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
	},

	//------------------------------------------------------------------------------------------------------------------

	send: function (data) {
		data.ref = this.session;
		this.application.fireEvent('send', data);
	},

	getServiceNode: function (address) {
		var store = this.getServicesStore();
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
