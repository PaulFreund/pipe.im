//======================================================================================================================

Ext.define('PipeUI.view.dialog.Command', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.window.Window',
	xtype: 'pipe-dialog-command',

	//------------------------------------------------------------------------------------------------------------------

	title: 'Command',
	closable: true,
	resizable: true,
	draggable: true,
	modal: true,

	bodyPadding: 10,

	//------------------------------------------------------------------------------------------------------------------

	items: {
		xtype: 'component',
		height: '90%',
		width: '90%',
		id: 'editor_holder'
	},

	buttons: [{
		text: 'Send',
		handler: 'doSend'
	}],

	//------------------------------------------------------------------------------------------------------------------

	controller: Ext.create('Ext.app.ViewController', {
		init: function() {
			this.view.on('afterrender', this.onAfterRender, this);
			this.view.on('destroy', this.onDestroy, this);
		},

		onAfterRender: function () {
			debugger;
			this.editor = new JSONEditor(document.getElementById('editor_holder'), {
				ajax: false,
				no_additional_properties: true,
				required_by_default: true,
				disable_edit_json: true,
				disable_collapse: true,
				disable_array_reorder: true,
				disable_properties: true,
				theme: 'jqueryui',
				iconlib: 'fontawesome4',

				schema: this.view.schema,
			});
		},

		onDestroy: function() {
			if(this.editor) { this.editor.destroy(); }
		},

		doSend: function () {
			var errors = this.editor.validate();
			if(errors.length) { debugger; }

			this.view.onSend(this.editor.getValue());
			
		}
	})

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================
