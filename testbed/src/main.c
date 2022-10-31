#include <lithium.h>

int main(void)
{
	LiArena *arena = liArenaCreate(liGigabytes(4), 8);

	LiWindow *window = liWindowCreate(arena, 800, 600, "Vulkan window");

	while (!liWindowClosed(window)) {
		liLogInfo("Window open!");
		liWindowPollEvents(window);
	}

	// Cleanup
	liWindowDestroy(window);
	liArenaDestroy(arena);
	return 0;
}
