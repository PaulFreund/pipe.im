# pipe.im

Scriptable online communication

## Build instructions

### Windows
* Install MSVC2013
* Download the [external](http://lvl3.org/pipe_external.7z) folder and extract it to the root or create your own folder
* Open project with MSVC2013 and compile

### Linux
* Install GCC >= 4.8.2
* Install CMake >= 2.8
* Install the current master of [Poco](https://github.com/pocoproject/poco) (checkout master, configure with --omit=Data/ODBC)
* Install glib
* Install libpurple >= 2.10.9
* Build Pipe
    * run cmake CMakeLists.txt
    * run make
    * run make install

### OS X
* Install CMake >= 2.8 (brew install cmake)
* Install PkgConfig (brew install pkgconfig)
* Install glib (brew install glib)
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