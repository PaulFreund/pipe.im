import std.stdio;

/* TODO  ===================

* Complete derelict glib/purple
 * Make modules out of files
 * Convert function definitions
 * import files in mains

==========================*/ 


import derelict.glib.glib;
import derelict.purple.purple;
import nullclient;

int main(string[] argv)
{
    DerelictGlib.load();
    DerelictPurple.load();

    writeln("pip.im initialize");
    
    int ret = nullclient.nullclient();

    return ret;
}

