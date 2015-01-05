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

Ext.define('PipeManagerUI.view.login.LoginWindowController', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.app.ViewController',
	alias: 'controller.loginController',

	//------------------------------------------------------------------------------------------------------------------

	onSpecialKey: function (field, e) {
		if (e.getKey() === e.ENTER) {
			this.onLogin();
		}
	},

	//------------------------------------------------------------------------------------------------------------------

	onLogin: function () {
		var myself = this;
		var form = this.lookupReference('loginForm').getForm();
		if (form) {
			form.submit({
				success: function (form, action) {
					myself.fireViewEvent('loginComplete', myself.getView());
				},
				failure: function (form, action) {
					var msg = 'Error';
					switch (action.failureType) {
						case Ext.form.action.Action.CLIENT_INVALID:
							msg = 'Please supply valid login data';
							break;
						case Ext.form.action.Action.CONNECT_FAILURE:
							msg = 'Login failed';
							if (action.response) { msg += ': ' + action.response.responseText; }
							break;
					}					
					
					Ext.Msg.alert('Error', msg);
				}
			});
		}
		else {
			Ext.Msg.alert('Error', 'Form could not be found');
		}
	}

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================

Ext.define('PipeManagerUI.view.login.LoginWindow', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.window.Window',
	xtype: 'pipemanager-login-loginwindow',
	controller: 'loginController',

	//------------------------------------------------------------------------------------------------------------------

	title: 'Login',
	closable: false,
	resizable: false,
	draggable: false,
	modal: true,

	bodyPadding: 10,

	//------------------------------------------------------------------------------------------------------------------

	items: {
		xtype: 'form',
		reference: 'loginForm',
		url: '/rest/login',
		defaultType: 'textfield',

		items: [{
			name: 'account',
			fieldLabel: 'Account',
			allowBlank: false,
			enableKeyEvents: true,
			listeners: {
				specialKey: 'onSpecialKey'
			}
		}, {
			name: 'password',
			inputType: 'password',
			fieldLabel: 'Password',
			allowBlank: false,
			enableKeyEvents: true,
			listeners: {
				specialKey: 'onSpecialKey'
			}
		}],
	},

	buttons: [{
		text: 'Login',
		handler: 'onLogin'
	}]

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================
