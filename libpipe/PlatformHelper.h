//======================================================================================================================

#pragma once

//======================================================================================================================

bool fileExists(const tstring& path);
bool fileIsDirectory(const tstring& path);
bool fileIsFile(const tstring& path);
bool fileCanRead(const tstring& path);
bool fileCanWrite(const tstring& path);
bool fileCreateFile(const tstring& path);
bool fileCreateDirectory(const tstring& path);
bool fileCreateDirectories(const tstring& path);
std::vector<tstring> fileDirectoryContents(const tstring& path);

//======================================================================================================================
