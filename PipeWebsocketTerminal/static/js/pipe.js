$().ready(function () {
    var pipeServer = new WebSocket("ws://" + window.location.host + window.location.pathname.substr(0, window.location.pathname.lastIndexOf("/")) + "/ws");

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
            prompt: 'pipe> ',
            onBlur: function() {
                return false;
            }
        });
    }

    var newAddressToken = 'New address: ';
    pipeServer.onmessage = function (message) {
        var messageText = message.data.toString();
        if (messageText.indexOf(newAddressToken) == 0) {
            var newAddress = messageText.substr(newAddressToken.length).trim();
            window.terminal.set_prompt(newAddress + '>');
        }
        else {
            window.terminal.echo(messageText);
        }
    }
});