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
					if(ph.res(msg, 'data.children.length') > 0) {
						Ext.iterate(msg.data.children, function (child) {
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
