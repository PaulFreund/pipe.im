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
            greetings: 'Welcome to the pipe.im shell\n',
            name: 'pipe_shell',
            prompt: 'pipe.im> ',
            onBlur: function() {
                return false;
            }
        });
    }

    pipeServer.onmessage = function (message) {
        window.terminal.echo(message.data);
    }
});