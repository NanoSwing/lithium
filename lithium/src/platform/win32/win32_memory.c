#include "base/base_context_crack.h"
#ifdef LI_OS_WINDOWS

#include "platform/platform_memory.h"

#include <Windows.h>

static U64 internal_liSnapToPages(U64 value)
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	U64 snapped = value;
	snapped += si.dwPageSize - 1;
	snapped -= snapped % si.dwPageSize;
	return snapped;
}

void *liMemoryReserve(U64 size)
{
	U64 snapped = internal_liSnapToPages(size);
	void* ptr = VirtualAlloc(NULL, snapped, MEM_RESERVE, PAGE_NOACCESS);
	return ptr;
}

void liMemoryCommit(void *ptr, U64 size)
{
	U64 snapped = internal_liSnapToPages(size);
	VirtualAlloc(ptr, snapped, MEM_COMMIT, PAGE_READWRITE);
}

void liMemoryDecommit(void *ptr, U64 size)
{
	VirtualFree(ptr, size, MEM_DECOMMIT);
}

void liMemoryRelease(void *ptr)
{
	VirtualFree(ptr, 0, MEM_RELEASE);
}

U64 liMemoryCalculateCommit(U64 size)
{
	return internal_liSnapToPages(size);
}


#endif // LI_OS_WINDOWS