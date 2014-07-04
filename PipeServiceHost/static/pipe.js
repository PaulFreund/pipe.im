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
    // Retrieves the children at the pipe address, onSuccess gets the resulting JSON object as parameter
    self.nodeChildren = function(address, onSuccess, onError) {
        self.get('rest/' + 'nodeChildren' + '/' + address, onSuccess, onError);
    };

    //------------------------------------------------------------------------------------------------------------------
    // Retrieves the command types for the node, onSuccess gets the resulting JSON object as parameter
    self.nodeCommandTypes = function(address, onSuccess, onError) {
        self.get('rest/' + 'nodeCommandTypes' + '/' + address, onSuccess, onError);
    };

    //------------------------------------------------------------------------------------------------------------------
    // Retrieves the message types for the node, onSuccess gets the resulting JSON object as parameter
    self.nodeMessageTypes = function(address, onSuccess, onError) {
        self.get('rest/' + 'nodeMessageTypes' + '/' + address, onSuccess, onError);
    };

    //------------------------------------------------------------------------------------------------------------------
    // Retrieves the node information, onSuccess gets the resulting JSON object as parameter
    self.nodeInfo = function(address, onSuccess, onError) {
        self.get('rest/' + 'nodeInfo' + '/' + address, onSuccess, onError);
    };

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
