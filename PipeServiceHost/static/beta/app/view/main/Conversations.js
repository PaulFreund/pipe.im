Ext.define('PipeUI.view.main.Conversations', {
    extend: 'Ext.tab.Panel',
	xtype: 'pipe-main-conversations',

	requires: [
	],
	
	defaults: {
		closable: true
	},
	
	items: [{
        title: 'Active Tab',
        html: "Hi"
    }, {
        title: 'Inactive Tab',
        html: "There"
    }, {
        title: 'Disabled Tab',
        disabled: true
    }],
	
});