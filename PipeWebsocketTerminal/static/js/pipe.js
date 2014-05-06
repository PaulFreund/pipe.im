$().ready(function () {
    var pipeServer = new WebSocket("ws://" + window.location.host + window.location.pathname.substr(0, window.location.pathname.lastIndexOf("/")) + "/ws");
    var currentAddress = 'pipe> ';
    pipeServer.onopen = function () {
        window.terminal = $('body').terminal(function (command, term) {
            if (command !== '') {
                try {
                    pipeServer.send(command);
                } catch (e) {
                    term.error(new String(e));
                }
            } else {
                term.echo('');
            }
        }, {
            greetings: '',
            name: 'pipe_shell',
            prompt: currentAddress,
            onBlur: function() {
                return false;
            }
        });
    }

    var tokenNewAddress = 'New address: ';
    var tokenQueryOptional = 'Do you want to add ';
    var tokenQueryValue = 'Value for ';
    var tokenCommandCompleted = 'Command completed';

    pipeServer.onmessage = function (message) {
        var messagesText = message.data.toString();
        var messages = messagesText.split('\n');
        for(var message in messages) {
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

                // Query value
            else if (messageText.trim().indexOf(tokenQueryValue) == 0) {
                window.terminal.set_prompt(messageText);
            }

                // Command completed
            else if (messageText.trim().indexOf(tokenCommandCompleted) == 0) {
                window.terminal.set_prompt(currentAddress);
                window.terminal.echo('');

            }

                // Output message
            else {
                window.terminal.echo(messageText);
            }
        }
    }
});