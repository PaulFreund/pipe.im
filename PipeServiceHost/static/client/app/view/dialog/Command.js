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
