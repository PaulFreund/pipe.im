//======================================================================================================================

Ext.define('PipeUI.view.conversation.BaseView', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'Ext.panel.Panel',

	//------------------------------------------------------------------------------------------------------------------

	layout: 'fit',
	closable: true,

	//------------------------------------------------------------------------------------------------------------------

	requires: [
		'PipeUI.view.BaseController'
	],

	controller: {
		type: 'baseController',

		onSession: function (session) {
			this.session = session;
		},

		onDisconnected: function () {
			this.session = undefined;
		},

		onMessage: function (msg) {
			if(!this.view || !this.view.address) { debugger; }
			if(msg.address != this.view.address) { return; }

			switch(msg.message) {
				case 'children':
				case 'node_added':
				case 'node_info_updated':
				case 'node_removed':
					break;

				case 'info':
					if(this.view && this.view.tab) {
						this.view.tab.setText(msg.data.instance_name);
						this.view.tab.setTooltip(msg.data.instance_description);
					}

					if(this.onInfo) { this.onInfo(msg.data); }
					break;

				default:
					if(this.onReceived) { this.onReceived(msg); }
					break;
			}
		},

		//--------------------------------------------------------------------------------------------------------------

		onActivate: function () {
			if(this.view && this.view.tab) {
				try {
					this.view.tab.setGlyph(0);
				}
				catch(e) { }
			}
		},

		//--------------------------------------------------------------------------------------------------------------

		highlight: function () {
			if(this.view && this.view.tab && !this.view.tab.active) {
				this.view.tab.setGlyph(126);
			}
		}
	},

	//------------------------------------------------------------------------------------------------------------------

	listeners: {
		scope: 'controller',
		activate: 'onActivate',
		beforedestroy: 'onBeforeDestroy'
	},

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================
