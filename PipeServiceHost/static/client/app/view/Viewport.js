//======================================================================================================================

Ext.define('PipeUI.view.Viewport', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.container.Viewport',

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
				xtype: 'pipe-status'
			},
			{
				region: 'west',
				floatable: false,
				split: true,
				collapsible: true,
				width: 300,
				xtype: 'pipe-browser'
			},
			{
				collapsible: false,
				region: 'center',
				xtype: 'pipe-conversationhost',
				bodyPadding: 10
			}
		]
	}]

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================