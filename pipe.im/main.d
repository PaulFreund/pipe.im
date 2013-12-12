import std.stdio;

extern (Windows): int TestFunction();

int main(string[] argv)
{
    writeln("Hello D-World!");
    TestFunction();
    return 0;
}
