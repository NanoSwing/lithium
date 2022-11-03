#include <lithium.h>

int main(void)
{
	LiArena *arena = liArenaCreate(liGigabytes(4), 8);

	LiWindow *window = liWindowCreate(arena, 800, 600, "Vulkan window", false);

	while (!liWindowClosed(window)) {
		liWindowPollEvents(window);
	}

	// Cleanup
	liWindowDestroy(window);
	liArenaDestroy(arena);
	return 0;
}
