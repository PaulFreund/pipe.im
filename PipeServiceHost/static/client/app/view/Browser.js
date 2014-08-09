//======================================================================================================================

Ext.define('PipeUI.view.Browser', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.tree.Panel',
	xtype: 'pipe-browser',

	//------------------------------------------------------------------------------------------------------------------

	store: 'Services',

	//------------------------------------------------------------------------------------------------------------------

	title: 'Browser',
	rootVisible: false,

	//------------------------------------------------------------------------------------------------------------------

	controller: {
		type: 'baseController',

		onInit: function () {
			this.view.on('select', this.onServiceSelect, this);
		},

		onServiceSelect: function (row, record, index, opts) {
			Ext.GlobalEvents.fireEvent('browser_service_selected', record.data.address);
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
			switch(msg.message) {
				case 'children':
					if(msg.data && msg.data.length > 0) {
						Ext.Array.forEach(msg.data, function (child) {
							this.send({ address: child, command: 'children' });
							this.send({ address: child, command: 'info' });
						}, this);
					}
					break;

				case 'info':
					var node = this.createService(msg.address);
					node.set('text', msg.data.state.name);
					node.set('type', msg.data.type);
					node.set('description', msg.data.description);
					node.set('state', msg.data.state);
					node.set('commands', msg.data.commands);
					node.set('messages', msg.data.messages);
					break;

				case 'node_added':
					this.send({ address: msg.address, command: 'info' });
					break;

				case 'node_removed':
					var node = this.getService(msg.address);
					if(node) { node.erase(); }
					break;

				case 'state':
				case 'state_updated':
					var node = this.getService(msg.address);
					if(node) { node.set('state', msg.data); }
					break;
			}
		},

		createService: function (address) {
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
				parent = this.createService(path.join('.'));
			}

			if(!parent.data.expandable)
				parent.set('expandable', true);

			// Create new child node
			var newChild = parent.createNode({
				address: address,
				text: address,
				expandable: false,
			});

			parent.appendChild(newChild);
			return newChild;
		}
	}

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================
