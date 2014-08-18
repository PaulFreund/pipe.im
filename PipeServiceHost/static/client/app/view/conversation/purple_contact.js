//======================================================================================================================

Ext.define('PipeUI.view.conversation.purple_contact', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'PipeUI.view.conversation.BaseView',
	xtype: 'pipe-conversation-purple_contact',

	//------------------------------------------------------------------------------------------------------------------

	statics: {
		constants: {
			defaults: {
				creates: false,
				show: false
			},
			sent: {
				ignore: false,
			},
			types: {
				message: {
					creates: true,
					show: false,
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
