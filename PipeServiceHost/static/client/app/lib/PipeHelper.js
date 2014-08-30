ph = {
	res: function (obj, path) {
		var parts = path.split('.');
		for(var i = 0, l = parts.length; i < l; i++) {
			var part = parts[i];
			if(obj && part in obj) {
				obj = obj[part];
			}
			else {
				return null;
			}
		}

		return obj;
	},

	timeString: function (timestamp) {
		// UNIX timestamp * 1000 = JS timestamp
		var time = new Date(parseInt(timestamp) * 1000);
		var hours = time.getHours();
		var minutes = time.getMinutes();

		var res = '';
		if(hours < 10) { res += '0'; }
		res += hours;
		res += ':';
		if(minutes < 10) { res += '0'; }
		res += minutes;
		return res;
	}
};