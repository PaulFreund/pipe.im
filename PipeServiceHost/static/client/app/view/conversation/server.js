//======================================================================================================================

Ext.define('PipeUI.view.conversation.server', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.Container',
	xtype: 'pipe-conversation-server',

	//------------------------------------------------------------------------------------------------------------------

	controller: 'serverController',

	//------------------------------------------------------------------------------------------------------------------

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
	]

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================

Ext.define('PipeUI.view.conversation.serverController', {
	extend: 'PipeUI.view.conversation.BaseController',
	alias: 'controller.serverController',

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
	},

	getMessages: function () {
		var grid = this.lookupReference('messages');
		if(!grid) { return null; }
		return grid.getStore();
	}
});

//======================================================================================================================
