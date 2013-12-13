import std.stdio;

import derelict.glib.glib;
import derelict.purple.purple;

int main(string[] argv)
{
    DerelictGlib.load();
    DerelictPurple.load();

    writeln("Hello D-World!");
    purple_core_init("pipe.im");
    return 0;
}
