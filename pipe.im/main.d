import std.stdio;


extern (C) int TestFunction();


int main(string[] argv)
{
    writeln("Hello D-World!");
    TestFunction();
    return 0;
}
