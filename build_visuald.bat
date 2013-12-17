set DELFILE=del /Q /F /A

rmdir /Q /S "AppData"
%DELFILE% "pipe.im.sln"
%DELFILE% "pipe.im.suo"
%DELFILE% "pipe.im.*.suo"
%DELFILE% "pipe.im.visualdproj"
dub generate visuald-combined