//======================================================================================================================

Ext.define('PipeUI.view.Viewport', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.container.Viewport',
	xtype: 'pipe-main-main',

	requires: [
		'Ext.layout.container.Border',
		'PipeUI.view.main.Status',
		'PipeUI.view.main.Browser',
		'PipeUI.view.main.Conversations'
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
				xtype: 'pipe-main-status'
			},
			{
				region: 'west',
				floatable: false,
				split: true,
				collapsible: true,
				width: 300,
				minWidth: 150,
				maxWidth: 300,
				xtype: 'pipe-main-browser'
			},
			{
				collapsible: false,
				region: 'center',
				xtype: 'pipe-main-conversations',
				bodyPadding: 10
			}
		]
	}]

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================