//======================================================================================================================

Ext.define('PipeUI.view.conversation.BaseController', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'PipeUI.view.BaseController',
	alias: 'controller.conversation.baseController',

	//------------------------------------------------------------------------------------------------------------------

	init: function () {
		var myself = this;

		this.callParent(arguments);
		this.view.on('activate', this.onActivate, this);
		
		if(this.view && this.view.address) {

			var service = this.getService(this.view.address);
			if(!service || !service.data || !service.data.commands) { return; }

			var toolbarItems = [];
			for(var command in service.data.commands) {
				var cmd = service.data.commands[command];

				var cmdFkt = 'on_' + cmd.command;
				if(this[cmdFkt]) { continue; }

				toolbarItems.push({
					xtype: 'button',
					text: cmd.command,
					tooltip: cmd.description,
					handler: cmdFkt
				});

				this[cmdFkt] = function () {
					myself.send({ address: myself.view.address, command: 'command', data: cmd.command });
				};
			}

			this.view.addDocked({
				xtype: 'toolbar',
				dock: 'top',
				items: toolbarItems
			});
		}
	},

	//------------------------------------------------------------------------------------------------------------------

	onActivate: function () {
		if(this.view && this.view.tab) {
			try { this.view.tab.setGlyph(0); } catch(e) { }
		}
	},

	onSession: function (session) {
		this.session = session;
	},

	onDisconnected: function () {
		this.session = undefined;
	},

	onMessage: function (msg) {
		if(!this.view || !this.view.address) { debugger; }
		if(msg.address != this.view.address) { return; }

		switch(msg.message) {
			case 'children':
			case 'node_added':
			case 'node_info_updated':
			case 'node_removed':
				break;

			case 'state': 
			case 'state_updated':
				if(this.view && this.view.tab && msg.address !== 'pipe') {
					this.view.tab.setText(msg.data.name);
					this.view.tab.setTooltip(msg.data.description);
				}
				break;

			case 'info':
				if(this.view && this.view.tab && msg.address !== 'pipe') {
					this.view.tab.setText(msg.data.state.name);
					this.view.tab.setTooltip(msg.data.state.description);
				}

				if(this.onInfo) { this.onInfo(msg.data); }
				break;

			case 'command':
				if(msg.data && msg.data.name && msg.data.schema) { this.onCommand(msg.data.name, msg.data.schema); }
				break;

			default:
				if(this.onReceived) { this.onReceived(msg); }
				break;
		}
	},

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

	highlight: function () {
		if(this.view && this.view.tab && !this.view.tab.active) {
			this.view.tab.setGlyph(126);
		}
	}

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================
