//======================================================================================================================

#include "CommonHeader.h"
#include "UserInstanceManager.h"

#include <Poco/File.h>
#include <Poco/Path.h>
#include <Poco/DirectoryIterator.h>

using namespace std;
using namespace Poco;
using namespace Poco::Util;
using namespace Poco::Net;

//======================================================================================================================

const tstring UserInstanceManager::UsersFolderName = _T("users");

//======================================================================================================================

UserInstanceConnection::UserInstanceConnection(const StreamSocket& socket) 
	: TCPServerConnection(socket)
{

}

//----------------------------------------------------------------------------------------------------------------------

void UserInstanceConnection::run() {
	StreamSocket& ss = socket();
	try {
		// TODO: Communicate with instance :)
		/*
		char buffer[256];
		int n = ss.receiveBytes(buffer, sizeof(buffer));
		while(n > 0) {
			ss.sendBytes(buffer, n);
			n = ss.receiveBytes(buffer, sizeof(buffer));
		}
		*/
	}
	catch(Poco::Exception& exc) {
		std::cerr << "EchoConnection: " << exc.displayText() << std::endl;
	}
}

//======================================================================================================================

UserInstanceManager::UserInstanceManager() {

	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());

	// Instance management server
	_socket = make_shared<ServerSocket>(SocketAddress(pApp->_instanceAddress, pApp->_instancePort));

	TCPServerParams* pParams = new TCPServerParams();
	pParams->setMaxThreads(1000);

	_server = make_shared<TCPServer>(new TCPServerConnectionFactoryImpl<UserInstanceConnection>(), *_socket, pParams);
	_server->start();

	if(prepareUsersDataPath())
		loadUsers();
}

//----------------------------------------------------------------------------------------------------------------------

UserInstanceManager::~UserInstanceManager() {
	_instances.clear();
	_server->stop();
}

//----------------------------------------------------------------------------------------------------------------------

void UserInstanceManager::loadUsers() {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());

	// Iterate over user directorys
	for(DirectoryIterator it(_usersDataPath), itEnd; it != itEnd; ++it) {
		File userDirectory(it->path());
		if(!userDirectory.exists() || !userDirectory.canRead() || !userDirectory.isDirectory()) { continue; }

		// Check if user file exist
		File userFile(Path(Path(userDirectory.path()), UserInstance::UserFileName));
		if(!userFile.exists() || !userFile.canRead() || !userFile.isFile()) { continue; }

		Path userDirectoryPath(userDirectory.path());
		tstring username = userDirectoryPath.getFileName();
		_instances[username] = make_shared<UserInstance>(userDirectory.path());
	}
}

//----------------------------------------------------------------------------------------------------------------------

void UserInstanceManager::createUser(const tstring& address, const tstring& password) {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());

	File userDirectory(_usersDataPath + Path::separator() + address);
	if(_instances.count(address) != 0 || userDirectory.exists()) {
		pApp->onError(_T("User already exists"));
		return;
	}

	userDirectory.createDirectory();
	if(!userDirectory.exists() || !userDirectory.canRead() || !userDirectory.isDirectory()) { return; }

	_instances[address] = make_shared<UserInstance>(userDirectory.path(), address, password);
}

//----------------------------------------------------------------------------------------------------------------------

void UserInstanceManager::deleteUser(const tstring& address) {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());

	if(_instances.count(address) == 0) {
		pApp->onError(_T("User could not be deleted"));
		return;
	}

	_instances.erase(address);
	File userDirectory(_usersDataPath + Path::separator() + address);
	userDirectory.remove(true);
}

//----------------------------------------------------------------------------------------------------------------------

bool UserInstanceManager::prepareUsersDataPath() {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());

	// Prepare data directory
	File dataPath(pApp->_datadir);
	if(!dataPath.exists()) { dataPath.createDirectory(); }

	if(!dataPath.exists() || !dataPath.canRead() || !dataPath.isDirectory()) {
		pApp->onError(_T("Could not open or create data folder"));
		return false;
	}

	// Prepare user data path
	tstring userDataDir = pApp->_datadir;
	if(userDataDir[userDataDir.size() - 1] != Path::separator()) { userDataDir += Path::separator(); }
	userDataDir += UserInstanceManager::UsersFolderName;

	File userDataPath(userDataDir);
	if(!userDataPath.exists()) { userDataPath.createDirectory(); }

	if(!userDataPath.exists() || !userDataPath.canRead() || !userDataPath.isDirectory()) {
		pApp->onError(_T("Could not open or create data folder"));
		return false;
	}

	_usersDataPath = userDataPath.path();
	return true;
}

//======================================================================================================================
