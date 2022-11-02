#include <lithium.h>

int main(void)
{
	LiArena *arena = liArenaCreate(liGigabytes(4), 8);

	liLogFatal("Cool");
	liLogError("Cool");
	liLogWarn("Cool");
	liLogInfo("Cool");
	liLogDebug("Cool");
	liLogTrace("Cool");

	// LiWindow *window = liWindowCreate(arena, 800, 600, "Vulkan window", false);

	// while (!liWindowClosed(window)) {
	// 	liWindowPollEvents(window);
	// }

	// // Cleanup
	// liWindowDestroy(window);
	liArenaDestroy(arena);
	return 0;
}
