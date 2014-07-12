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
    self.connect = function (uri, onSuccess, onError) {
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
    }

    //------------------------------------------------------------------------------------------------------------------
}

//======================================================================================================================
