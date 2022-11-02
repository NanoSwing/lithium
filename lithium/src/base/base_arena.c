#include "base/base_arena.h"
#include "base/base_types.h"
#include "base/base_logging.h"
#include "platform/platform_threading.h"
#include "platform/platform_memory.h"

#include <stddef.h>
#include <string.h>

struct LiArena {
	void *pool;
	// Offset from the beginning of pool.
	U64 position;
	// How much of pool has been commited.
	U64 commit_pos;
	// Max amount of memory reserved.
	U64 max;
	// Memory alignment.
	U64 align;
};

// Decommit memory if possible.
static void internal_liArenaSetPosition(LiArena *arena, U64 position)
{
	// Only push position backwards so no memory is memory is skipped.
	if (arena->position > position) {
		arena->position = position;

		// Calculate decommit amount.
		U64 decommit_position = liMemoryCalculateCommit(position);
		U64 over_commited = arena->commit_pos - decommit_position;
		over_commited -= over_commited % liMemoryCalculateCommit(1);
		// Decommit if possible.
		if (decommit_position > 0) {
			liMemoryDecommit((U8 *) arena->pool + decommit_position, over_commited);
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
	// Align size.
	U64 aligned_size = size;
	aligned_size += arena->align - 1;
	aligned_size -= aligned_size % arena->align;

	// Save current arena position for return value.
	U64 root_position = arena->position;

	// Offset size within the pool.
	arena->position += aligned_size;
	if (arena->position > arena->commit_pos) {
		liMemoryCommit(arena->pool, arena->position);
		arena->commit_pos = liMemoryCalculateCommit(arena->position);
	}

	// Check for over allocation.
	if (arena->commit_pos > arena->max) {
		liLogWarn("Arena out of memory!");
		return NULL;
	}

	return (U8 *) arena->pool + root_position;
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
