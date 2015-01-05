//======================================================================================================================
/*
	Copyright (c) since 2015 - Paul Freund (freund.paul@lvl3.org)
	
	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:
	
	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/
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

void* libraryLoad(const tstring& path);
void libraryUnload(void* handle);
bool libraryHasSymbol(void* handle, const tstring& name);
void* libraryGetSymbol(void* handle, const tstring& name);

//======================================================================================================================
