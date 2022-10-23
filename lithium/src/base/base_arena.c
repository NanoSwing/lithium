#include "base/base_arena.h"
#include "platform/platform_threading.h"
#include "platform/platform_memory.h"

struct LiArena {
	void *pool;
	LiMutex *mutex;
	U64 position;
	U64 commit_pos;
	U64 max;
	U64 align;
};

LiArena *liArenaCreate(U64 size, U64 align)
{
	LiArena *arena = liMemoryReserve(size + sizeof(LiArena));
}

void liArenaDestroy(LiArena *arena)
{
}
