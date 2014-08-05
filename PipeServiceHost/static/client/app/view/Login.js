//======================================================================================================================

Ext.define('PipeUI.view.Login', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.window.Window',
	xtype: 'pipe-login',
	controller: 'LoginController',

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

Ext.define('PipeUI.view.LoginController', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.app.ViewController',
	alias: 'controller.LoginController',

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
