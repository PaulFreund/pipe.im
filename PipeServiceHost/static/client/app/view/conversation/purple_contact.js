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

Ext.define('PipeUI.view.conversation.purple_contact', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'PipeUI.view.conversation.BaseView',
	xtype: 'pipe-conversation-purple_contact',

	//------------------------------------------------------------------------------------------------------------------

	statics: {
		constants: {
			renderers: {
				message: function (msg) {
					var res = '';
					// Add Date
					res += '[' + ph.timeString(msg.timestamp) + '] ';

					if(msg.command && msg.command === 'say') { res += 'Me: ' }
					res += msg.data;

					return res;
				},
			},
			commands: {
				defaults: {
					show: true
				},
				say: {
					show: true,
					renderer: 'message'
				}
			},
			messages: {
				defaults: {
					creates: false,
					show: false
				},
				message: {
					creates: true,
					show: true,
					sent: false,
					renderer: 'message'
				}
			}
		}
	},

	//------------------------------------------------------------------------------------------------------------------

	initComponent: function () {
		this.callParent(arguments);

		this.add({
			layout: {
				type: 'hbox',
				align: 'stretch'
			},
			items: [
				{
					name: 'sendText',
					reference: 'sendText',
					xtype: 'textfield',
					flex: true,
					allowBlank: false,
					enableKeyEvents: true,
					listeners: { specialKey: 'onSpecialKey' }
				},
				{
					xtype: 'button',
					text: 'Send',
					handler: 'on_say',
					margin: '0 0 0 10'
				}
			]
		});
	},

	//------------------------------------------------------------------------------------------------------------------

	controller: {
		onSpecialKey: function (field, e) {
			if(e.getKey() === e.ENTER) {
				this.on_say();
			}
		},

		on_say: function () {
			var textBox = this.lookupReference('sendText');
			var outgoing = textBox.value;
			textBox.reset();

			this.send({ address: this.view.address, command: 'say', data: outgoing });
		}
	}

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================
