#include "base/base_error.h"
#include "platform/platform_windowing.h"
#include <lithium.h>

void errCallback(const LiError error)
{
	switch (error.severity) {
		case LI_ERROR_SEVERITY_HEAVY:
			liLogFatal("%s", error.message.c_str);
			break;
		case LI_ERROR_SEVERITY_MEDIUM:
			liLogError("%s", error.message.c_str);
			break;
		case LI_ERROR_SEVERITY_LIGHT:
			liLogWarn("%s", error.message.c_str);
			break;
	}
}

I32 main(void)
{
	liErrorInit();
	liErrorCallback(errCallback);
	LiArena *arena = liArenaCreate(liGigabytes(4), 8);

	LiWindow *window = liWindowCreate(arena, 800, 600, "Lithium window", false);

	while (!liWindowClosed(window)) {
		liWindowPollEvents(window);
	}

	// Cleanup
	liWindowDestroy(window);
	liArenaDestroy(arena);
	liErrorCleanup();
	return 0;
}
