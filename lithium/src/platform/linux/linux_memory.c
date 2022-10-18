#include "base/base_context_crack.h"

#ifdef LI_OS_LINUX

#include "platform/platform_memory.h"

#include <sys/mman.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

// Reserve memory  - mmap
// Commit memory   - madvise
// Decommit memory - madvise
// Free memory     - munmap

void *liMemoryReserve(Usize size)
{
	// Snap memory to page size
	I32 snapped = size;
	snapped += getpagesize() - 1;
	snapped -= snapped % getpagesize();

	void *ptr = mmap(NULL, size, PROT_NONE, MAP_PRIVATE | MAP_ANON, -1, 0);
	return ptr;
}

void liMemoryCommit(void *ptr, Usize size)
{
	// Snap memory to page size
	I32 snapped = size;
	snapped += getpagesize() - 1;
	snapped -= snapped % getpagesize();

	mprotect(ptr, size, PROT_READ | PROT_WRITE);
	madvise(ptr, size, MADV_WILLNEED);
}

void liMemoryDecommit(void *ptr, Usize size)
{
	// Snap memory to page size
	I32 snapped = size;
	snapped += getpagesize() - 1;
	snapped -= snapped % getpagesize();

	mprotect(ptr, size, PROT_NONE);
	madvise(ptr, size, MADV_DONTNEED);
}

void liMemoryRelease(void *ptr)
{
	munmap(ptr, 0);
}

#endif // LI_OS_LINUX
