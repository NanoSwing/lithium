#include "platform/platform_memory.h"
#include <lithium.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	// Reserve 4 GB
	void *ptr = liMemoryReserve(4 * 10E9);
	
	// 1 Gigabyte
	Usize commit_size = (1 * 10E9) / 8;
	liMemoryCommit(ptr, commit_size);
	memset(ptr, 0, commit_size);

	liMemoryDecommit(ptr, commit_size);
	liMemoryRelease(ptr);

	return 0;
}
