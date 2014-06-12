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
    
## Testing with PipeWebsocketTerminal

    PipeWebsocketTerminal --extdir=/usr/local/lib/pipe --staticdir=/usr/local/share/pipe/WebsocketTerminal/static --datadir=pipedata --port=4242 --address="0.0.0.0" --uripath=shell

The installation prefix in this example is "/usr/local" and data will be stored in `pwd`/pipedata (can be changed with --datadir).

For quick development of the web ui, delete /usr/local/share/pipe/WebsocketTerminal/static and create a symlink (ln -s ...)
