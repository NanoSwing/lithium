#include "platform/platform_filesystem.h"
#include <lithium.h>

int main(void)
{
	LiArena *arena = liArenaCreate(liGigabytes(4), 8);

	liArenaDestroy(arena);
	return 0;
}
