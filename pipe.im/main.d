import std.stdio;

/* TODO  ===================

* Complete derelict glib/purple
 * Make modules out of files
 * Convert function definitions
 * import files in mains

==========================*/ 


import derelict.glib.glib;
//fit import derelict.purple.purple;

int main(string[] argv)
{
    DerelictGlib.load();
    //DerelictPurple.load();

    writeln("Hello D-World!");
    purple_core_init("pipe.im");
    return 0;
}
