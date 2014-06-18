$().ready(function () {
	var pipe = new Pipe(window.location.host + '/pipe');
	pipe.nodeChildren('pipe.services', function(body) { console.log(body); });
	
	pipe.shellConnect(
		function(socket) {
			window.terminal = $('body').terminal(function (command, term) {
				if (command !== '') {
					try {
						socket.send(command);
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
			
			var currentAddress = 'pipe> ';

			var tokenNewAddress = 'New address: ';
			var tokenQueryOptional = 'Do you want to add ';
			var tokenQueryValue = 'Value for ';
			var tokenCommandCompleted = 'Command completed';

			socket.onmessage = function (message) {
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

		},
		function(error) {
			term.error(new String(error));
		}
	);	
});