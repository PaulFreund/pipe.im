//======================================================================================================================

window.currentAddress = 'pipe';
window.authenticated = false;

window.setPrompt = function (prompt) {
    window.terminal.set_prompt(prompt);
};

window.setCurrentAddress = function (address) {
    if(address !== undefined)
        window.currentAddress = address;

    window.setPrompt(window.currentAddress + '> ');
};

window.getCookie = function (name) {
    var value = "; " + document.cookie;
    var parts = value.split("; " + name + "=");
    if (parts.length == 2) return parts.pop().split(";").shift();
};

window.requestREST = function (uri, onSuccess, onError, data) {
    var req = new XMLHttpRequest();
    req.open(data === undefined ? 'get' : 'post', 'http://' + window.location.host + '/rest/' + uri);

    req.onreadystatechange = function () {
        if (req.readyState === 4) {
            if (req.status === 200) {
                if (onSuccess !== undefined)
                    onSuccess(req.responseText);
            }
            else {
                if (onError !== undefined)
                    onError(req.status);
            }
        }
    }
    req.send(data === undefined ? null : data);
};

//======================================================================================================================

window.authenticate = function () {
    window.terminal.set_mask(false);

    window.requestREST('authenticated', function (data) {
        if (data === 'true') {
            window.authenticated = true;
            window.startShell();
        }
        else {
            var account = '';

            window.terminal.echo('');
            window.terminal.echo('Please login');
            window.terminal.echo('');
            window.setPrompt('Account: ');

            window.onShellInput = function (input) {
                if (account.length === 0) {
                    account = input;
                    window.setPrompt('Password: ');
                    window.terminal.set_mask(true);
                }
                else {
                    window.setCurrentAddress();
                    var loginData = 'account=' + encodeURIComponent(account);
                    loginData += '&'
                    loginData += 'password=' + encodeURIComponent(input);

                    window.requestREST('login', function (data) {
                        window.startShell();
                    }, function (error) {
                        window.terminal.echo('Invalid login data');
                        window.authenticated = false;
                        window.authenticate();
                        return;
                    }, loginData);
                }
            };
        }
    }, function (error) {
        window.authenticated = false;
        window.authenticate();
        return;
    });
};

window.startShell = function () {
    window.terminal.set_mask(false);

    var token = window.getCookie('session');
    if (token == undefined || token.length == 0) {
        window.authenticated = false;
        authenticate();
        return;
    }

    var pipe = new Pipe(window.location.host);

    pipe.shellConnect(
		function (socket) {
		    window.onShellInput = function (input) {
		        if (input == 'logout') {
		            window.requestREST('logout', function (data) {
		                window.authenticated = false;
		                window.authenticate();
		            }
                    , function (error) {
                        window.terminal.echo('Logout failed');
                    });
		        }
		        else {
		            socket.send(input);
		        }
		    };

		    socket.send('connection_shell=' + token);

		    var currentAddress = 'pipe> ';

		    var tokenNewAddress = 'New address: ';
		    var tokenQueryOptional = 'Do you want to add ';
		    var tokenQueryDefault = 'Do you want to use the default value ';
		    var tokenQueryValue = 'Value for ';
		    var tokenChooseEnum = 'Please choose an option';
		    var tokenCommandCompleted = 'Instance completed';
		    var tokenCommandAborted = 'Aborted command'

		    socket.onmessage = function (message) {
		        var messagesText = message.data.toString();
		        var messages = messagesText.split('\n');
		        for (var message in messages) {
		            var messageText = messages[message];
		            // New address
		            if (messageText.indexOf(tokenNewAddress) == 0) {
		                var newAddress = messageText.substr(tokenNewAddress.length).trim();
		                currentAddress = newAddress + '> ';
		                window.terminal.set_prompt(currentAddress);
		            }

		                // Query optional
		            else if (messageText.trim().indexOf(tokenQueryOptional) == 0) {
		                window.terminal.set_prompt(messageText);
		            }

		                // Query default
		            else if (messageText.trim().indexOf(tokenQueryDefault) == 0) {
		                window.terminal.set_prompt(messageText);
		            }

		                // Query enum
		            else if (messageText.trim().indexOf(tokenChooseEnum) == 0) {
		                window.terminal.set_prompt(messageText);
		            }

		                // Query value
		            else if (messageText.trim().indexOf(tokenQueryValue) == 0) {
		                window.terminal.set_prompt(messageText);
		            }

		                // Command completed
		            else if (messageText.trim().indexOf(tokenCommandCompleted) == 0) {
		                window.terminal.set_prompt(currentAddress);
		                window.terminal.echo('');
		            }

		                // Command aborted
		            else if (messageText.trim().indexOf(tokenCommandAborted) == 0) {
		                window.terminal.set_prompt(currentAddress);
		                window.terminal.echo('');
		            }


		                // Output message
		            else {
		                window.terminal.echo(messageText);
		            }
		        }
		    }

		},
		function (error) {
		    term.error(new String(error));
		    window.authenticated = false;
		    window.authenticate();
		}
	);
};

//======================================================================================================================

$().ready(function () {
    window.terminal = $('body').terminal(function (input, term) {
        try {
            if (window.onShellInput != undefined && window.onShellInput != null)
                window.onShellInput(input);
        } catch (e) {
            term.error(new String(e));
        }
    }, {
        greetings: '',
        name: 'pipe_shell',
        prompt: window.currentAddress + '> ',
        onBlur: function () {
            return false;
        }
    });

    window.authenticate();
});

//======================================================================================================================
