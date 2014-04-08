#include <libpipe/LibPipeItf.h>

#include <algorithm>
#include <exception>
#include <iostream>
#include <map>
#include <array>
#include <string>
using namespace std;

#include <Poco/Util/Application.h>
using namespace Poco;
using namespace Poco::Util;

class PipeShellApplication : public Application {
public:
	PipeShellApplication(int argc, char* argv[]) : Application(argc, argv) {}
	~PipeShellApplication() {}
};


int main(int argc, char* argv[]) {

	try {
		PipeShellApplication self(argc, argv);
		Path commandPath(self.commandPath());

		//Pipe::Pipe pipeInstance;
		//pipeInstance.loadExtensions(commandPath.parent().toString());
		//pipeInstance.run();
	}
	catch(exception e) {
		cout << "Exception: " << e.what() << endl;
	}
	
	cin.get();
	return 0;
}
