//======================================================================================================================

Ext.define('PipeUI.view.Viewport', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.container.Viewport',
	xtype: 'pipe-main-main',

	requires: [
		'Ext.layout.container.Border',
		'PipeUI.view.status.Status',
		'PipeUI.view.browser.Browser',
		'PipeUI.view.conversations.ConversationHost'
	],

	//------------------------------------------------------------------------------------------------------------------

	layout: 'fit',

	items: [{
		xtype: 'panel',
		layout: 'border',

		defaults: {
			collapsible: false,
			split: false,
		},

		items: [
			{
				region: 'north',
				height: 50,
				minHeight: 50,
				maxHeight: 50,
				xtype: 'pipe-status-status'
			},
			{
				region: 'west',
				floatable: false,
				split: true,
				collapsible: true,
				width: 300,
				xtype: 'pipe-browser-browser'
			},
			{
				collapsible: false,
				region: 'center',
				xtype: 'pipe-conversation-conversation-host',
				bodyPadding: 10
			}
		]
	}]

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================