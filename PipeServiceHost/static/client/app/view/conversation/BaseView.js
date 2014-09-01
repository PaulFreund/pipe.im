//======================================================================================================================

Ext.define('PipeUI.view.conversation.BaseView', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.panel.Panel',

	//------------------------------------------------------------------------------------------------------------------
	
	layout: {
		type: 'vbox',
		align: 'stretch'
	},

	//------------------------------------------------------------------------------------------------------------------

	items: [{
		xtype: 'grid',
		reference: 'messages',
		hideHeaders: true,
		autoScroll: true,
		border: false,
		columnLines: false,
		enableColumnResize: false,
		rowLines: false,
		flex: 1,
		store: {
			fields: [
				{ name: 'message', type: 'auto' }
			]
		},
		columns: [
			{
				text: 'Message',
				dataIndex: 'message',
				flex: 1,
				cellWrap: true,
				renderer: 'renderMessage'
			}
		],
	}],

	//------------------------------------------------------------------------------------------------------------------

	controller: {
		//--------------------------------------------------------------------------------------------------------------

		type: 'baseController',

		//--------------------------------------------------------------------------------------------------------------

		onInit: function () {
			var myself = this;

			if(!this.view) { return; }
			this.view.on('activate', this.onActivate, this);

			if(!this.view.address) { return; }

			var service = this.getService(this.view.address);
			if(!service || !service.data || !service.data.commands) { return; }

			var toolbarItems = [];
			Ext.iterate(service.data.commands, function (cmd) {
				var cmdFkt = 'on_' + cmd.command;
				if(this[cmdFkt]) { return; }

				toolbarItems.push({
					xtype: 'button',
					text: cmd.command,
					tooltip: cmd.description,
					handler: cmdFkt
				});

				this[cmdFkt] = function () {
					myself.send({ address: myself.view.address, command: 'command', data: cmd.command });
				};
			}, this);

			this.view.addDocked({
				xtype: 'toolbar',
				dock: 'top',
				items: toolbarItems
			});
		},

		//--------------------------------------------------------------------------------------------------------------

		onMessage: function (msg) {
			if(!this.view || !this.view.address) { debugger; }
			if(msg.address != this.view.address) { return; }

			if(msg.message === 'command') {
				if(msg.data && msg.data.name && msg.data.schema) { this.onCommand(msg.data.name, msg.data.schema); }
				return;
			}

			var show = false;
			if((resConst = ph.res(this, 'view.self.constants.messages')) !== null) {
				if((resDefault = ph.res(resConst, 'defaults.show')) !== null) { show = resDefault; }
				if((resType = ph.res(resConst, msg.message + '.show')) !== null) { show = resType; }
			}

			if(show) {
				this.addMessage(msg);
				this.highlight();
			}
		},

		//--------------------------------------------------------------------------------------------------------------

		onActivate: function () {
			if(this.view && this.view.tab) {
				try { this.view.tab.setGlyph(0); } catch(e) { }
			}

			this.scrollToBottom();
		},

		//--------------------------------------------------------------------------------------------------------------

		onSent: function (msg) {
			if(!this.view || !this.view.address) { debugger; }
			if(msg.address != this.view.address) { return; }

			var show = false;
			if((resConst = ph.res(this, 'view.self.constants.commands')) !== null) {
				if((resDefault = ph.res(resConst, 'defaults.show')) !== null) { show = resDefault; }
				if((resType = ph.res(resConst, msg.command + '.show')) !== null) { show = resType; }
			}

			if(show) { this.addMessage(msg); }
		},

		//--------------------------------------------------------------------------------------------------------------

		onCommand: function (command, schema) {
			if(!this.view || !this.view.address) { return; }
			if(!schema) {
				this.send({
					command: command,
					address: myself.view.address
				});
			}

			var myself = this;
			this.commandWindow = Ext.create('PipeUI.view.dialog.Command', {
				autoShow: true,
				schema: schema,
				onSend: function (result) {
					myself.send({
						command: command,
						address: myself.view.address,
						data: result
					});
					myself.commandWindow.destroy();
				}
			});
		},

		//--------------------------------------------------------------------------------------------------------------

		getMessages: function () {
			var grid = this.lookupReference('messages');
			if(!grid) { return null; }
			return grid.getStore();
		},

		//--------------------------------------------------------------------------------------------------------------

		addMessage: function (message) {
			var store = this.getMessages();
			if(!store) { return; }

			store.add({ message: message });

			this.scrollToBottom();
		},

		//--------------------------------------------------------------------------------------------------------------

		scrollToBottom: function () {
			var grid = this.lookupReference('messages');
			if(!grid) { return; }
			var gridView = grid.getView();
			if(!gridView) { return; }

			try { gridView.scrollBy(0, 999999, true); } catch(e) { }
		},

		//--------------------------------------------------------------------------------------------------------------

		highlight: function () {
			if(this.view && this.view.tab && !this.view.tab.active) {
				this.view.tab.setGlyph(126);
			}
		},

		//--------------------------------------------------------------------------------------------------------------

		renderMessage: function (msg) {
			if(!msg || (!msg.message && !msg.command)) { return; }

			var renderer = null;
			var name = msg.command ? msg.command : msg.message;
			var source = msg.command ? 'view.self.constants.commands' : 'view.self.constants.messages';
			if((resConst = ph.res(this, source)) !== null) {
				if((resDefault = ph.res(resConst, 'defaults.renderer')) !== null) { renderer = resDefault; }
				if((resType = ph.res(resConst, name + '.renderer')) !== null) { renderer = resType; }
			}

			if(typeof (renderer) === 'string') {
				if((resRend = ph.res(this, 'view.self.constants.renderers.' + renderer)) !== null) {
					renderer = resRend;
				}
			}

			if(renderer) { return renderer(msg); }

			var res = '';
			// Add Date
			res += '[' + ph.timeString(msg.timestamp) + '] ';

			// Add type
			res += '&lt;' + (msg.command ? ('out:' + msg.command) : (msg.message)) + '&gt;  ';

			// Add Data
			if(msg.data) {
				res += (typeof (msg.data) === 'string') ? msg.data : JSON.stringify(msg.data);
			}

			return res;
		}

		//--------------------------------------------------------------------------------------------------------------
	}

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================
