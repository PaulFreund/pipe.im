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
		this.send({ address: 'pipe', command: 'info' });

		var store = this.getServicesStore();

		store.add(PipeUI.model.ServiceNode.create({
			id: 'pipe',
			address: 'pipe',
			text: "Pipe",
			leaf: true,
			data: {}
		}));

		store.add(PipeUI.model.ServiceNode.create({
			id: 'pipe.test',
			address: 'pipe.test',
			text: "Test",
			leaf: true,
			data: {}
		}));

		debugger;

		store.getNodeById('pipe').add(PipeUI.model.ServiceNode.create({
			id: 'pipe.blarg',
			text: "Blarg",
			leaf: true,
			data: {}
		}));

	},

	onDisconnected: function () {
		var store = this.getServicesStore();
		store.removeAll();
		this.session = undefined;
	},

	onMessage: function (msg) {
		if (msg.message === 'children') {
			if (msg.data && msg.data.length > 0) {
				Ext.Array.forEach(msg.data, function (child) {
					//var node = this.getServiceNode(child);
					//node.text = child;
					this.send({ address: child, command: 'children' });
					this.send({ address: child, command: 'info' });
				}, this);
			}
		}
		else if (msg.message === 'info') {
			//var node = this.getServiceNode(child);
			//node.text = msg.data.instance_name;
			//node.data = msg.data;
		}
	},

	//------------------------------------------------------------------------------------------------------------------

	send: function (data) {
		data.ref = this.session;
		this.application.fireEvent('send', data);
	},

	getServiceNode: function(address) {
		var store = this.getServicesStore();


		var path = address.split('.');
		debugger;
		var currentNode = store.getRoot();
		for (seg in path) {
			/*
			if (!path.hasOwnProperty(seg)) { continue; }
			var node = currentNode.getNodeById(path[seg]);
			if(!node) { currentNode.add(); }
			currentNode = 
			*/
		}
		store.getNodeById()

		store.add(PipeUI.model.ServiceNode.create({
			id: address,
			text: address,
			data: {}
		}));
	}
});

//======================================================================================================================
