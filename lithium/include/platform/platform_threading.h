#ifndef LI_PLATFORM_THREADING_H
#define LI_PLATFORM_THREADING_H

#include "base/base_types.h"
#include "base/base_defines.h"
#include "base/base_arena.h"

// Thread handle.
typedef I64 LiThread;
// Mutex handle.
typedef struct LiMutex LiMutex;
// Function ran by a thread.
typedef void *(*LiThreadFunc)(void *arg);

// Starts a new thread and returns the handle. Arg will be passed to thread_func.
LIAPI LiThread liThreadCreate(LiThreadFunc thread_func, void *arg);
// Waits until thread has finished its operation. Thread_func return value will be placed in output if output isn't NULL.
LIAPI void liThreadWait(LiThread thread, void **output);
// Gets thread handle of current thread.
LIAPI LiThread liThreadGetSelf(void);

// Create mutex.
LIAPI LiMutex *liMutexCreate(LiArena *arena);
// Destroy mutex.
LIAPI void liMutexDestroy(LiMutex *mutex);
// Lock mutex.
LIAPI void liMutexLock(LiMutex *mutex);
// Unlock mutex.
LIAPI void liMutexUnlock(LiMutex *mutex);

#endif // LI_PLATFORM_THREADING_H
