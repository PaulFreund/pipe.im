//======================================================================================================================

Ext.define('PipeManagerUI.view.Viewport', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.container.Viewport',
	xtype: 'pipemanager-main-main',

	requires: [
		'Ext.layout.container.Border',
		'PipeManagerUI.view.header.Header',
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
				xtype: 'pipemanager-header-header'
			},
			{
				collapsible: false,
				region: 'center',
				layout: 'center',

				items: [{
					height: '80%',
					layout: {
						type: 'hbox',
						align: 'stretch'
					},

					defaults: {
						xtype: 'button',
						scale: 'large',
						flex: 1,
						margin: '80%',
						hrefTarget: '_self'
					},
					items: [
						{
							text: 'Client',
							href: 'client/',
						},
						{
							text: 'Shell',
							href: 'shell/'
						}
					]
				}]
			}
		]
	}]

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================