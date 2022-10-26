#include <lithium.h>

#include <stdio.h>
#include <string.h>

int main(void)
{
	LiArena *arena = liArenaCreate(liGigabytes(4), 8);

	liLogFatal("Cool");
	liLogError("Cool");
	liLogWarn("Cool");
	liLogInfo("Cool");
	liLogDebug("Cool");
	liLogTrace("Cool");

	liArenaDestroy(arena);
	return 0;
}
