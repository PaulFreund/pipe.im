//======================================================================================================================

Ext.define('PipeUI.view.conversation.server', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.Container',
	xtype: 'pipe-conversation-server',

	//------------------------------------------------------------------------------------------------------------------

	controller: 'serverController',

	//------------------------------------------------------------------------------------------------------------------
	layout: 'fit',

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
					text: 'Message',
					dataIndex: 'message',
					flex: 20
				}
			],
		}
	],

	listeners: {
		scope: 'controller',
		activate: 'onActivate'
	}

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================

Ext.define('PipeUI.view.conversation.serverController', {
	extend: 'PipeUI.view.conversation.BaseController',
	alias: 'controller.serverController',

	onActivate: function () {
		var view = this.getView();
		if(view && view.tab) {
			try {
				view.tab.setGlyph(0);
			}
			catch(e) { }
		}

		this.scrollToBottom();
	},

	onInfo: function (info) {

	},

	onSession: function () {
		this.onReceived('Got Session');
	},

	onDisconnected: function() {
		this.onReceived('Disconnected');
		Ext.GlobalEvents.fireEvent('connection_connect');
	},

	onReceived: function (msg) {
		this.addMessage(JSON.stringify(msg));
	},

	onServerMessage: function (msg) {
		this.onReceived(msg);
	},


	addMessage: function (message) {
		var store = this.getMessages();
		if(!store) { return; }

		store.add({
			timestamp: Ext.Date.format(new Date(), 'H:i'),
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
});

//======================================================================================================================
