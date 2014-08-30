//======================================================================================================================

Ext.define('PipeUI.view.conversation.server', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'PipeUI.view.conversation.BaseView',
	xtype: 'pipe-conversation-server',

	//------------------------------------------------------------------------------------------------------------------

	statics: {
		constants: {
			commands: {
				defaults: {
					show: false
				}
			},
			messages: {
				defaults: {
					creates: false,
					show: false
				}
			}
		}
	},

	//------------------------------------------------------------------------------------------------------------------
	
	controller: {
		onSession: function () {
			this.addMessage(this.createMessage('Got Session'));
		},

		onDisconnected: function () {
			this.addMessage(this.createMessage('Disconnected'));
		},

		createMessage: function(text) {
			return {
				address: 'pipeui.server',
				timestamp: Math.round(new Date().getTime() / 1000),
				ref: this.session,
				message: 'status',
				data: text
			};
		}
	},

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================
