#include "base/base_context_crack.h"
#include "base/base_types.h"

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

static U64 internal_liSnapToPages(U64 value)
{
	U64 snapped = value;
	snapped += getpagesize() - 1;
	snapped -= snapped % getpagesize();
	return snapped;
}

void *liMemoryReserve(U64 size)
{
	U64 snapped = internal_liSnapToPages(size + sizeof(U64));
	U64 *ptr = mmap(NULL, snapped, PROT_NONE, MAP_PRIVATE | MAP_ANON, -1, 0);
	mprotect(ptr, sizeof(U64), PROT_READ | PROT_WRITE);
	*ptr = snapped;

	return (void *) ptr + sizeof(U64);
}

void liMemoryCommit(void *ptr, U64 size)
{
	void *correct_ptr = ptr - sizeof(U64);
	U64 snapped = internal_liSnapToPages(size + sizeof(U64));
	mprotect(correct_ptr, snapped, PROT_READ | PROT_WRITE);
	madvise(correct_ptr, snapped, MADV_WILLNEED);
}

void liMemoryDecommit(void *ptr, U64 size)
{
	mprotect(ptr, size, PROT_NONE);
	madvise(ptr, size, MADV_DONTNEED);
}

void liMemoryRelease(void *ptr)
{
	void *correct_ptr = ptr - sizeof(U64);
	U64 size = *(U64 *) correct_ptr;
	munmap(correct_ptr, size);
}

#endif // LI_OS_LINUX
