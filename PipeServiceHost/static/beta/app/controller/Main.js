Ext.define('PipeUI.controller.Main', {
    extend: 'Ext.app.Controller',

	requires: [
    'PipeUI.view.main.Main',
    'PipeUI.view.login.LoginWindow'
	],

	onLaunch: function () {
        this.login = new PipeUI.view.login.LoginWindow({
        //    session: session,
            autoShow: true,
            listeners: {
                scope: this,
                close: 'onLogin' // TODO: Change to login
            }
        });
    },

	onLogin: function () {
        this.login.destroy();

        //this.loginManager = loginManager;
        //this.organization = organization;
        //this.user = user;

        this.viewport = new PipeUI.view.main.Main({
            session: this.session,
            viewModel: {
                data: {
                    currentOrg: this.organization,
                    currentUser: this.user
                }
            }
        });
    },
});
