#ifndef LI_PLATFORM_WINDOWING_H
#define LI_PLATFORM_WINDOWING_H

#include "base/base_defines.h"
#include "base/base_arena.h"
#include <vulkan/vulkan.h>

typedef struct LiWindow LiWindow;

LIAPI LiWindow *liWindowCreate(LiArena *arena, U32 width, U32 height, const char *title, B8 resizable);
LIAPI void liWindowDestroy(LiWindow *window);
LIAPI void liWindowPollEvents(LiWindow *window);
LIAPI B8 liWindowClosed(const LiWindow *window);
LIAPI VkSurfaceKHR liWindowGetSurface(const LiWindow *window, VkInstance instance);

#endif // LI_PLATFORM_WINDOWING_H
