//======================================================================================================================

#pragma once

//======================================================================================================================

bool fileExists(tstring& path);
bool fileIsDirectory(tstring& path);
bool fileIsFile(tstring& path);
bool fileCanRead(tstring& path);
bool fileCanWrite(tstring& path);
bool fileCreate(tstring& path);
bool fileCreateDirectories(tstring& path);

//======================================================================================================================
