# pipe.im

Modular, scriptable communication router

TL;DR:
* Centralize multiple channels like Facebook, ICQ, IRC, IMAP, POP3, SMS etc...
* Automate communication with scripts, like: "Send me a SMS when Felix sends me an E-Mail"
* Translate between channels, e.g.: Chat with your facebook friends from Steam

## Intro

All services and librarys are implemented in C++ using features of C++11. One of the design goals is to have few dependencies, the core library libpipe has no dependencies except for a C++11 compilant compiler.
Another design goal was to build everything modular and platform independent. Pipe works on Windows, Linux and OSX and has pure C interfaces for interfacing to libpipe and writing pipe services. A easy to use C++ interface layer is also included.

This repository currently consists of four projects
* libpipe: Plugin-based library for multi channel communication and automation
* PipeExtensionPurple: Enables communicating with libpurple supported networks (e.g. ICQ, IRC, Facebook, ...)
* PipeServiceHost & PipeServiceInstance: Web+Websocket server for SaaS hosting of pipe instances including a ExtJS based Webinterface

## Todo

* libpipe
	* Default DOM should be restructured
	* Provide access to DOM in root node and scripting
	* Scripting should be modular and not embedded in libpipe
* PipeExtensionPurple
	* Implement all missing features
	* Figure out how to handle contacts outside of the contact list
* PipeServiceHost & PipeServiceInstance
	* Implement admin interface
	* Implement user management commands
* Write a Qt based client
* Documentation

## Build instructions

### Windows
* Install MSVC2013
* Download the [external](http://lvl3.org/pipe_external.7z) folder and extract it to the root or create your own folder
* Open project with MSVC2013 and compile

### Linux
* Install GCC >= 4.9.1
* Install CMake >= 2.8
* Install the current master of [Poco](https://github.com/pocoproject/poco)
	* run git checkout master
	* run ./configure --omit=XML,JSON,Data,Data/SQLite,MongoDB,Data/MySQL,Data/ODBC,CppParser,PDF,Zip,PageCompiler --no-samples --no-tests
* Install glib
* Install libpurple >= 2.10.9
* Build Pipe
    * run cmake CMakeLists.txt
    * run make
    * run make install

### OS X Mavericks
* Install XCode and XCode Command-Line tools
* Install CMake >= 2.8 (brew install cmake)
* Install PkgConfig (brew install pkgconfig)
* Install libpurple (brew install finch)
* Install the current master of [Poco](https://github.com/pocoproject/poco)
    * run git checkout master
	* run ./configure --config=Darwin-clang-libc++ --omit=XML,JSON,Data,Data/SQLite,MongoDB,Data/MySQL,Data/ODBC,CppParser,PDF,Zip,PageCompiler --no-samples --no-tests
    * run make
	* run make install
* Build Pipe
    * run cmake CMakeLists.txt
    * run make
    * run make install
	
## Used open source projects

* libpipe
	* [Ductape](https://github.com/svaarala/duktape)
	* a modified version of [JSON11](https://github.com/dropbox/json11)
* PipeExtensionPurple
	* [libpurple](http://pidgin.im/)
* PipeServiceHost & PipeServiceInstance
	* [Poco](https://github.com/pocoproject/poco)