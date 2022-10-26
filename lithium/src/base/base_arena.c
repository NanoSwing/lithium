#include "base/base_arena.h"
#include "base/base_types.h"
#include "base/base_logging.h"
#include "platform/platform_threading.h"
#include "platform/platform_memory.h"

#include <stddef.h>
#include <string.h>

struct LiArena {
	void *pool;
	U64 position;
	U64 commit_pos;
	U64 max;
	U64 align;
};

static void internal_liArenaSetPosition(LiArena *arena, U64 position)
{
	if (arena->position > position) {

		arena->position = position;

		U64 decommit_position = liMemoryCalculateCommit(position);
		U64 over_commited = arena->commit_pos - decommit_position;
		over_commited -= over_commited % liMemoryCalculateCommit(1);
		if (decommit_position > 0) {
			liMemoryDecommit(arena->pool + decommit_position, over_commited);
			arena->commit_pos -= over_commited;
		}
	}
}

LiArena *liArenaCreate(U64 size, U64 align)
{
	LiArena *arena = liMemoryReserve(sizeof(LiArena));
	liMemoryCommit(arena, sizeof(LiArena));
	arena->pool = liMemoryReserve(size);
	arena->position = 0;
	arena->commit_pos = 0;
	arena->max = liMemoryCalculateCommit(size);
	arena->align = align;

	return arena;
}

void liArenaDestroy(LiArena *arena)
{
	liMemoryRelease(arena->pool);
	liMemoryRelease(arena);
}

void *liArenaPush(LiArena *arena, U64 size)
{
	U64 aligned_size = size;
	aligned_size += arena->align - 1;
	aligned_size -= aligned_size % arena->align;

	arena->position += aligned_size;
	if (arena->position > arena->commit_pos) {
		liMemoryCommit(arena->pool, arena->position);
		arena->commit_pos = liMemoryCalculateCommit(arena->position);
	}

	if (arena->commit_pos > arena->max) {
		liLogWarn("Arena out of memory!");
		return NULL;
	}

	return arena->pool + arena->position;
}

void *liArenaPushZero(LiArena *arena, U64 size)
{
	void *mem = liArenaPush(arena, size);
	memset(mem, 0, size);
	return mem;
}

void liArenaPop(LiArena *arena, U64 size) { internal_liArenaSetPosition(arena, arena->position - size); }
void liArenaReset(LiArena *arena) { internal_liArenaSetPosition(arena, 0); }

LiArenaTemp liArenaTempBegin(LiArena *arena)
{
	return (LiArenaTemp) { arena, arena->position };
}

void liArenaTempEnd(LiArenaTemp arena)
{
	internal_liArenaSetPosition(arena.arena, arena.pos);
}
