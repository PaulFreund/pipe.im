//======================================================================================================================

Ext.define('PipeUI.view.conversation.purple_contact', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.Container',
	xtype: 'pipe-conversation-purple_contact',

	//------------------------------------------------------------------------------------------------------------------

	controller: 'purple_contactController',

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
			flex: true,
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

	listeners: {
		scope: 'controller',
		activate: 'onActivate'
	}

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================

Ext.define('PipeUI.view.conversation.purple_contactController', {
	extend: 'PipeUI.view.conversation.BaseController',
	alias: 'controller.purple_contactController',

	onInfo: function (info) {

	},

	onReceived: function (msg) {
		if(msg.message !== 'message') { return; }

		var sep = msg.data.indexOf(':');
		var nick = msg.data.substr(0, sep);
		var message = msg.data.substr(sep+1);

		this.addMessage(nick, message);

		var view = this.getView();
		if(!view.isVisible() && view.tab) { view.tab.setGlyph(99); }// TODO: Changes when visible
	},

	onSpecialKey: function (field, e) {
		if(e.getKey() === e.ENTER) {
			this.onSend();
		}
	},

	onActivate: function() {
		var view = this.getView(); 
		try {
			view.tab.setGlyph(0);
		}
		catch(e) { }

		//var grid = this.lookupReference('messages');
		//if(!grid || !grid.isVisible()) { return null; }
		//grid.scrollBy(0, 999999, true); // TODO: Fix
	},

	addMessage: function(nick, message) {
		var store = this.getMessages();
		if(!store) { return; }

		var newItem = store.add({
			timestamp: Ext.Date.format(new Date(), 'H:i'),
			nick: '&lt;' + nick + '&gt;',
			message: message
		});

		var grid = this.lookupReference('messages');
		if(!grid || !grid.isVisible()) { return null; }
		grid.focus(newItem);
	},

	onSend: function () {
		var textBox = this.lookupReference('sendText');
		var outgoing = textBox.value;
		textBox.reset();

		var view = this.getView();
		this.send({ address: view.address, command: 'say', data: outgoing });

		this.addMessage('Me', outgoing);
	},

	getMessages: function () {
		var grid = this.lookupReference('messages');
		if(!grid) { return null; }
		return grid.getStore();
	}
});

//======================================================================================================================
