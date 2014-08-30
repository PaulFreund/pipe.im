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
