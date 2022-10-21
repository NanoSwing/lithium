#include "platform/platform_threading.h"
#include <lithium.h>

#include <stddef.h>
#include <stdio.h>

LiMutex *lock;

#define COUNT_TO ((U64) 1E6)

void *threadFunc(void *arg)
{
	(void) arg;

	static U64 i = 0;

	for (;;) {
		liMutexLock(lock);

		if (i >= COUNT_TO) {
			liMutexUnlock(lock);
			return NULL;
		}
		i++;

		liMutexUnlock(lock);
		printf("%llu\n", i);
	}
}

int main(void)
{
	lock = liMutexCreate();

	LiThread thread[8];
	for (U32 i = 0; i < 8; i++) {
		thread[i] = liThreadCreate(threadFunc, NULL);
	}
	for (U32 i = 0; i < 8; i++) {
		liThreadWait(thread[i], NULL);
		liThreadDestroy(thread[i]);
	}

	liMutexDestroy(lock);
	return 0;
}
