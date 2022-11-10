#include "platform/platform_windowing.h"
#include <lithium.h>

I32 main(void)
{
	LiArena *arena = liArenaCreate(liGigabytes(4), 8);

	LiWindow *window = liWindowCreate(arena, 800, 600, "Lithium window", false);

	while (!liWindowClosed(window)) {
		liWindowPollEvents(window);
	}

	// Cleanup
	liWindowDestroy(window);
	liArenaDestroy(arena);
	return 0;
}
