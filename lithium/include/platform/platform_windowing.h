#ifndef LI_PLATFORM_WINDOWING_H
#define LI_PLATFORM_WINDOWING_H

#include "base/base_defines.h"
#include "base/base_arena.h"
#include <vulkan/vulkan.h>

// Window handle.
typedef struct LiWindow LiWindow;

// Create a window.
LIAPI LiWindow *liWindowCreate(LiArena *arena, U32 width, U32 height, const char *title, B8 resizable);
// Destroy winodw.
LIAPI void liWindowDestroy(LiWindow *window);
// Poll for window events.
LIAPI void liWindowPollEvents(LiWindow *window);
// If a close event has been sent, this will return true.
LIAPI B8 liWindowClosed(const LiWindow *window);
// Get a vulkan surface from window.
LIAPI VkSurfaceKHR liWindowGetSurface(const LiWindow *window, VkInstance instance);

#endif // LI_PLATFORM_WINDOWING_H
