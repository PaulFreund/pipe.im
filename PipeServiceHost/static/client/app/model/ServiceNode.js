//======================================================================================================================

Ext.define('PipeUI.model.ServiceNode', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.data.TreeModel',

	//------------------------------------------------------------------------------------------------------------------

	idProperty: 'address',
	fields: [
		{ name: 'address', type: 'string' },
		{ name: 'info', type: 'auto' }
	],

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================