//======================================================================================================================

Ext.define('PipeUI.view.conversation.purple_contact', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'PipeUI.view.conversation.BaseView',
	xtype: 'pipe-conversation-purple_contact',

	//------------------------------------------------------------------------------------------------------------------

	statics: {
		shouldCreate: function (messageType) {
			// TODO
			return (messageType === 'message')
		}
	},

	//------------------------------------------------------------------------------------------------------------------

	gridModel: {
		fields: [
			{ name: 'timestamp' },
			{ name: 'nick' },
			{ name: 'message' },
		]
	},

	gridColumns: [
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

	//------------------------------------------------------------------------------------------------------------------

	initComponent: function () {
		this.callParent(arguments);

		this.add({
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
					handler: 'on_say',
					margin: '0 0 0 10'
				}
			]
		});
	},

	//------------------------------------------------------------------------------------------------------------------

	controller: {
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
				this.on_say();
			}
		},

		on_say: function () {
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
		}
	}

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================
