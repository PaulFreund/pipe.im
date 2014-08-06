//======================================================================================================================

Ext.define('PipeUI.view.conversation.BaseController', {
	extend: 'PipeUI.view.BaseController',

	onSession: function (session) {
		this.session = session;
	},

	onDisconnected: function () {
		this.session = undefined;
	},

	onMessage: function (msg) {
		var view = this.getView();
		if(!view.address) { debugger; }
		if(msg.address != view.address) { return; }

		switch(msg.message) {
			case 'children':
			case 'node_added':
			case 'node_info_updated':
			case 'node_removed':
				break;

			case 'info':
				if(view && view.tab) {
					view.tab.setText(msg.data.instance_name);
					view.tab.setTooltip(msg.data.instance_description);
				}

				if(this.onInfo) { this.onInfo(msg.data); }
				break;

			default:
				if(this.onReceived) { this.onReceived(msg); }

				if(view && view.tab && !view.tab.active) {
					view.tab.setGlyph(126);
				}

				break;
		}
	},

	onActivate: function () {
		var view = this.getView();
		if(view && view.tab) {
			try {
				view.tab.setGlyph(0);
			}
			catch(e) { }
		}
	}
});

//======================================================================================================================
