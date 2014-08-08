//======================================================================================================================

Ext.define('PipeUI.view.conversation.purple_contact', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.panel.Panel',
	xtype: 'pipe-conversation-purple_contact',

	//------------------------------------------------------------------------------------------------------------------
	
	layout: {
		type: 'vbox',
		align: 'stretch'
	},

	items: [
		{
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
					{ name: 'timestamp' },
					{ name: 'nick' },
					{ name: 'message' },
				]
			},
			columns: [
				{
					text: 'Timestamp',
					dataIndex: 'timestamp',
					flex: 2
				},
				{
					text: 'Nick',
					dataIndex: 'nick',
					flex: 5
				},
				{
					text: 'Message',
					dataIndex: 'message',
					flex: 20
				}
			],
		},
		{
			layout: {
				type: 'hbox',
				align: 'stretch'
			},
			items: [
				{
					name: 'sendText',
					reference: 'sendText',
					xtype: 'textfield',
					flex: true,
					allowBlank: false,
					enableKeyEvents: true,
					listeners: { specialKey: 'onSpecialKey' }
				},
				{
					xtype: 'button',
					text: 'Send',
					handler: 'onSend',
					margin: '0 0 0 10'
				}
			]
		}
	],

	//------------------------------------------------------------------------------------------------------------------

	controller: {
		type: 'conversation.baseController',

		onActivate: function () {
			if(this.view && this.view.tab) {
				try { this.view.tab.setGlyph(0); } catch(e) { }
			}

			this.scrollToBottom();
		},

		onInfo: function (info) {

		},

		onReceived: function (msg) {
			if(msg.message !== 'message') { return; }

			var sep = msg.data.indexOf(':');
			var nick = msg.data.substr(0, sep);
			var message = msg.data.substr(sep + 1);

			this.addMessage(nick, message);
			this.highlight();
		},

		onSpecialKey: function (field, e) {
			if(e.getKey() === e.ENTER) {
				this.onSend();
			}
		},

		onSend: function () {
			var textBox = this.lookupReference('sendText');
			var outgoing = textBox.value;
			textBox.reset();

			this.send({ address: this.view.address, command: 'say', data: outgoing });

			this.addMessage('Me', outgoing);
		},

		addMessage: function (nick, message) {
			var store = this.getMessages();
			if(!store) { return; }

			store.add({
				timestamp: Ext.Date.format(new Date(), 'H:i'),
				nick: '&lt;' + nick + '&gt;',
				message: message
			});

			this.scrollToBottom();
		},

		getMessages: function () {
			var grid = this.lookupReference('messages');
			if(!grid) { return null; }
			return grid.getStore();
		},

		scrollToBottom: function () {
			var grid = this.lookupReference('messages');
			if(!grid) { return; }
			var gridView = grid.getView();
			if(!gridView) { return; }

			try {
				gridView.scrollBy(0, 999999, true);
			}
			catch(e) { }
		}
	}

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================
