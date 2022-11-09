#include "base/base_error.h"
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
	liErrorCallback(errCallback);

	liError(LI_ERROR_SEVERITY_LIGHT, "Warn");
	liErrorFormat(LI_ERROR_SEVERITY_MEDIUM, "Error, %.5f", 3.14159f);
	liError(LI_ERROR_SEVERITY_HEAVY, "Fatal");

	U8 count = 0;
	const LiError *errs = liErrorGet(&count);
	for (U8 i = 0; i < count; i++) {
		liLogDebug("%s, %d", errs[i].message.c_str, errs[i].severity);
	}

	/* LiArena *arena = liArenaCreate(liGigabytes(4), 8); */

	/* LiWindow *window = liWindowCreate(arena, 800, 600, "Lithium window", false); */

	/* while (!liWindowClosed(window)) { */
	/* 	liWindowPollEvents(window); */
	/* } */

	/* // Cleanup */
	/* liWindowDestroy(window); */
	/* liArenaDestroy(arena); */
	return 0;
}
