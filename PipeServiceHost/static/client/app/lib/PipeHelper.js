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