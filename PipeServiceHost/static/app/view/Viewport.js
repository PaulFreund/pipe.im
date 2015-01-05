//======================================================================================================================
/*
	Copyright (c) since 2015 - Paul Freund (freund.paul@lvl3.org)
	
	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:
	
	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/
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