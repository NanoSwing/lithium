#ifndef LI_BASE_CONTEXT_CRACK_H
#define LI_BASE_CONTEXT_CRACK_H

////////////////////////////////////////////////////
// NanoSwing: Find OS

#ifdef __linux__
	#define LI_OS_LINUX
#endif // __linux__

#ifdef _WIN32
	#ifdef _WIN64
		#define LI_OS_WINDOWS
	#else
		#error "32-bit Windows isn't supported."
	#endif // _WIN64
#endif // _WIN32

#ifdef __APPLE__
	#define LI_OS_APPLE
#endif // __APPLE__

#endif // LI_BASE_CONTEXT_CRACK_H
