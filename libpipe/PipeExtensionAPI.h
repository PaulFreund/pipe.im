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

#ifdef WIN32
	#ifdef PIPE_EXTENSION_EXPORTS
		#define PIPE_EXTENSION_ITF extern "C" __declspec(dllexport) 
	#else
		#define PIPE_EXTENSION_ITF extern "C" __declspec(dllimport) 
	#endif
#else
	#define PIPE_EXTENSION_ITF extern "C"
#endif

//======================================================================================================================

typedef void*           HPipeExtensionService;
typedef const char*     PipeExtensionStr;

typedef void*           PipeExtensionCbContext;
typedef void            (*PipeExtensionCbErr)(PipeExtensionStr);
typedef void            (*PipeExtensionCbStr)(PipeExtensionCbContext, PipeExtensionStr);

//======================================================================================================================

PIPE_EXTENSION_ITF void PipeExtensionSetErrorCallback           (PipeExtensionCbErr cbError);
PIPE_EXTENSION_ITF void PipeExtensionSetPath                    (PipeExtensionStr path);

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionGetServiceTypes            (PipeExtensionCbContext context, PipeExtensionCbStr cbServiceTypes);

PIPE_EXTENSION_ITF void PipeExtensionServiceCreate              (PipeExtensionStr serviceType, PipeExtensionStr address, PipeExtensionStr settings, HPipeExtensionService* service);
PIPE_EXTENSION_ITF void PipeExtensionServiceDestroy             (HPipeExtensionService service);

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionProcess                    ();

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServicePush                (HPipeExtensionService service, PipeExtensionStr messages);
PIPE_EXTENSION_ITF void PipeExtensionServicePull                (HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbStr cbMessages);

//======================================================================================================================
