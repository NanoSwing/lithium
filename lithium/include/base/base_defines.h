#ifndef LI_BASE_DEFINES_H
#define LI_BASE_DEFINES_H

#include "base/base_context_crack.h"

#ifdef LI_OS_LINUX
	#ifdef LI_BUILD_DLL
		#define LIAPI __attribute__((visibility("default")))
	#else
		#define LIAPI
	#endif // LI_BUILD_DLL
#endif // LI_OS_LINUX

#ifdef LI_OS_WINDOWS
	#ifdef LI_BUILD_DLL
		#define LIAPI __declspec(dllexport)
	#else
		#define LIAPI __declspec(dllimport)
	#endif // LI_BUILD_DLL
#endif // LI_OS_WINDOWS

#endif // LI_BASE_DEFINES_H
