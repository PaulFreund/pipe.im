ph = {
	res: function (obj, path) {
		var parts = path.split('.');
		for(var i = 0, l = parts.length; i < l; i++) {
			var part = parts[i];
			if(obj && part in obj) {
				obj = obj[part];
			}
			else {
				return undefined;
			}
		}

		return obj;
	}
};