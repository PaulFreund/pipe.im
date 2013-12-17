import std.stdio;

/* TODO  ============================================================================

* Create external package derelict-glib
    * Create dub package
    * Publish dub package

* Create external package derelict-purple
    * Create dub package
    * Publish dub package

* Create pipe.im pakage
    * Create dub package
    * Test on Linux
    * Publish dub package

===================================================================================*/ 


import derelict.glib.glib;
import derelict.purple.purple;
import nullclient;

int main(string[] argv)
{
    DerelictGlib.load();
    DerelictPurple.load();

    writeln("pipe.im initialize");
    
    int ret = nullclient.nullclient();

    return ret;
}

