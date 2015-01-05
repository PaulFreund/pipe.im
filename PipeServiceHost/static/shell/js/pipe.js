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

function Pipe(basePath) {
    //------------------------------------------------------------------------------------------------------------------

    var self = this;

    //------------------------------------------------------------------------------------------------------------------
    // The basePath should point to the listening address and path of the server (for example localhost:9980/pipe)
    if (basePath !== undefined)
        self._basePath = basePath;
    else
        self._basePath = window.location.host;

    //------------------------------------------------------------------------------------------------------------------
    // Connect to pipe server, onSuccess gets the websocket as parameter
    self.pipeConnect = function (onSuccess, onError) {
        self.connect('ws', onSuccess, onError);
    }

    //------------------------------------------------------------------------------------------------------------------
    // Connect to pipe server with shell adapter, onSuccess gets the websocket as parameter
    self.shellConnect = function(onSuccess, onError) {
        self.connect('wss', onSuccess, onError);
    }

    //------------------------------------------------------------------------------------------------------------------
    // Internal helper for XHR requests
    self.get = function(uri, onSuccess, onError) {
        var req = new XMLHttpRequest();
        req.open('get', 'http://' + self._basePath + '/' + uri);
        req.onreadystatechange = function () {
            if(req.readyState === 4) {
                if (req.status === 200) {
                    if (onSuccess !== undefined)
                        onSuccess(req.responseText);
                }
                else {
                    if(onError !== undefined)
                        onError(req.status);
                }
            }
        }
        req.send(null);
    }

    //------------------------------------------------------------------------------------------------------------------
    // Internal helper for websocket connections
    self.connect = function (uri, onSuccess, onError, onClose) {
        var socket = new WebSocket('ws://' + self._basePath + '/' + uri);
        socket.onopen = function () {
            if (onSuccess !== undefined)
                onSuccess(socket)
            else
                socket.close();
        }
        socket.onerror = function (error) {
            if (onError !== undefined)
                onError(error);
        }
        socket.onclose = function (code, reason, wasClean) {
        	if (onClose !== undefined)
        		onClose(code, reason, wasClean);
        }
    }

    //------------------------------------------------------------------------------------------------------------------
}

//======================================================================================================================
