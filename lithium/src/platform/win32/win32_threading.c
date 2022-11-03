#include "base/base_context_crack.h"
#ifdef LI_OS_WINDOWS

#include "platform/platform_threading.h"
#include "base/base_logging.h"

#include <Windows.h>

struct LiMutex {
	HANDLE handle;
};

LiThread liThreadCreate(LiThreadFunc thread_func, void *arg)
{
	LiThread thread = 0;
	HANDLE handle = CreateThread(NULL, 0, thread_func, arg, 0, &thread);
	if (handle == NULL) {
		liLogError("Failed to create thread!");
		return -1;
	}
	CloseHandle(handle);

	return thread;
}

void liThreadWait(LiThread thread, void **output)
{
	HANDLE handle = OpenThread(SYNCHRONIZE, false, thread);
	if (handle == 0) {
		return;
	}
	WaitForSingleObject(handle, INFINITE);
}

LiThread liThreadGetSelf(void)
{
	return GetCurrentThreadId();
}

LiMutex *liMutexCreate(LiArena *arena)
{
	HANDLE handle = CreateMutex(NULL, false, NULL);
	if (handle == NULL) {
		liLogError("Failed to create mutex!");
		return NULL;
	}

	LiMutex* mutex = liArenaPush(arena, sizeof(LiMutex));
	mutex->handle = handle;
	return mutex;
}

void liMutexDestroy(LiMutex *mutex)
{
	CloseHandle(mutex->handle);
}

void liMutexLock(LiMutex *mutex)
{
	WaitForSingleObject(mutex->handle, INFINITE);
}

void liMutexUnlock(LiMutex *mutex)
{
	ReleaseMutex(mutex->handle);
}

#endif // LI_OS_WINDOWS