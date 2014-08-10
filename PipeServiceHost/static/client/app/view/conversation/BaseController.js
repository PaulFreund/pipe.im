//======================================================================================================================

Ext.define('PipeUI.view.conversation.BaseController', {
	//------------------------------------------------------------------------------------------------------------------

	extend: 'PipeUI.view.BaseController',
	alias: 'controller.conversation.baseController',

	//------------------------------------------------------------------------------------------------------------------

	init: function () {
		this.callParent(arguments);
		this.view.on('activate', this.onActivate, this);
	},

	//------------------------------------------------------------------------------------------------------------------

	onActivate: function () {
		if(this.view && this.view.tab) {
			try { this.view.tab.setGlyph(0); } catch(e) { }
		}
	},

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

			case 'state': 
			case 'state_updated':
				if(this.view && this.view.tab && msg.address !== 'pipe') {
					this.view.tab.setText(msg.data.name);
					this.view.tab.setTooltip(msg.data.description);
				}
				break;

			case 'info':
				if(this.view && this.view.tab && msg.address !== 'pipe') {
					this.view.tab.setText(msg.data.state.name);
					this.view.tab.setTooltip(msg.data.state.description);
				}

				if(this.onInfo) { this.onInfo(msg.data); }
				break;

			default:
				if(this.onReceived) { this.onReceived(msg); }
				break;
		}
	},

	//--------------------------------------------------------------------------------------------------------------

	highlight: function () {
		if(this.view && this.view.tab && !this.view.tab.active) {
			this.view.tab.setGlyph(126);
		}
	}

	//------------------------------------------------------------------------------------------------------------------
});

//======================================================================================================================
