#include "base/base_context_crack.h"

#ifdef LI_OS_LINUX

#include <pthread.h>
#include "platform/platform_threading.h"
#include "platform/platform_memory.h"

struct LiMutex {
	pthread_mutex_t mutex;
};

LiThread liThreadCreate(LiThreadFunc thread_func, void *arg)
{
	pthread_t thread;
	pthread_create(&thread, NULL, thread_func, arg);

	return (LiThread) thread;
}

void liThreadDestroy(LiThread thread)
{
	(void) thread;
	return;
}

void liThreadWait(LiThread thread, void **output)
{
	pthread_join(thread, output);
}

LiMutex *liMutexCreate(void)
{
	LiMutex *mutex = liMemoryReserve(sizeof(LiMutex));
	liMemoryCommit(mutex, sizeof(LiMutex));
	pthread_mutex_init(&mutex->mutex, NULL);
	return mutex;
}

void liMutexDestroy(LiMutex *mutex)
{
	liMemoryRelease(mutex);
}

void liMutexLock(LiMutex *mutex)
{
	pthread_mutex_lock(&mutex->mutex);
}

void liMutexUnlock(LiMutex *mutex)
{
	pthread_mutex_unlock(&mutex->mutex);
}

#endif // LI_OS_LINUX
