//======================================================================================================================

Ext.define('PipeUI.controller.Services', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.app.Controller',

	//------------------------------------------------------------------------------------------------------------------

	config: {
		listen: {
			global: {
				connection_session: 'onSession',
				connection_disconnected: 'onDisconnect',
				connection_message: 'onMessage',
			}
		}
	},

	//------------------------------------------------------------------------------------------------------------------

	onSession: function (session) {
		this.send({ address: 'pipe', command: 'info' });
	},

	onDisconnected: function () {
		var store = this.getServices();
		store.removeAll();
	},

	onMessage: function (msg) {
		switch(msg.message) {
			case 'info':
				var node = this.getService(msg.address);
				if(!node) {
					if(msg.address != 'pipe') {
						var parentAddress = msg.address.split('.').slice(0, -1).join('.');
						var parentNode = this.getServices();

						if(parentAddress && parentAddress != 'pipe') { parentNode = this.getService(parentAddress); }
						if(!parentNode) { break; }

						if(!parentNode.data.expandable)
							parentNode.set('expandable', true);

						// Create new child node
						node = parentNode.createNode({
							address: msg.address,
							text: msg.data.state.name,
							typeName: msg.data.type,
							description: msg.data.description,
							state: msg.data.state,
							children: msg.data.children,
							commands: msg.data.commands,
							messages: msg.data.messages,
							expandable: false
						});

						parentNode.appendChild(node);
						Ext.GlobalEvents.fireEvent('service_update', msg.address, node);
					}

					// Get info for children
					if(msg.data && msg.data.children && msg.data.children.length > 0) {
						Ext.Array.forEach(msg.data.children, function (child) {
							this.send({ address: child, command: 'info' });
						}, this);
					}
				}
				else {
					node.set('text', msg.data.state.name);
					node.set('typeName', msg.data.type);
					node.set('description', msg.data.description);
					node.set('state', msg.data.state);
					node.set('commands', msg.data.commands);
					node.set('messages', msg.data.messages);
					Ext.GlobalEvents.fireEvent('service_update', msg.address, node);
				}
				break;

			case 'node_added':
				this.send({ address: msg.data, command: 'info' });
				break;

			case 'node_removed':
				Ext.GlobalEvents.fireEvent('service_removed', msg.address);
				var node = this.getService(msg.data);
				if(node) { node.erase(); }
				break;

			case 'state':
			case 'state_updated':
				var node = this.getService(msg.address);
				if(node) { node.set('state', msg.data); }
				Ext.GlobalEvents.fireEvent('service_update', msg.address, node);
				break;
		}
	},

	send: function(data) {
		Ext.GlobalEvents.fireEvent('connection_send', data);
	},

	getServices: function () {
		var store = this.getStore('Services');
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
