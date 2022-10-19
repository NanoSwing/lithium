#include "platform/platform_memory.h"
#include <lithium.h>

#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

int main(void)
{
	// Reserve 2 GB
	U64 size = liGigabytes(2);
	void *ptr = liMemoryReserve(size);
	
	// Commit 1 GB
	U64 commit = liGigabytes(1);
	liMemoryCommit(ptr, commit);
	memset(ptr, 0, commit);

	sleep(2);

	liMemoryDecommit(ptr, commit);
	liMemoryRelease(ptr);

	sleep(2);

	return 0;
}
