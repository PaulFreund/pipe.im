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
