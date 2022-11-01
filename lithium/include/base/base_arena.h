#ifndef LI_BASE_ARENA_H
#define LI_BASE_ARENA_H

#include "base/base_types.h"
#include "base/base_defines.h"

// Memory arena. A stack like memory pool.
typedef struct LiArena LiArena;
// Temporary memory arena used to reset the memory arena once done using it.
typedef struct {
	LiArena *arena;
	U64 pos;
} LiArenaTemp;

// Create a memory arena. Reserve size amount of bytes but commits none.
LIAPI LiArena *liArenaCreate(U64 size, U64 align);
// Frees all reserved memory.
LIAPI void liArenaDestroy(LiArena *arena);

// Commits size amount of bytes.
LIAPI void *liArenaPush(LiArena *arena, U64 size);
// Commits size amount of bytes and sets them to 0.
LIAPI void *liArenaPushZero(LiArena *arena, U64 size);
// Discard size amount of bytes from the top of the arena.
LIAPI void liArenaPop(LiArena *arena, U64 size);
// Resets the arena to position 0. No data is lost but can be overwritten.
LIAPI void liArenaReset(LiArena *arena);

// Save arena state.
LIAPI LiArenaTemp liArenaTempBegin(LiArena *arena);
// Revert back to previous arena state.
LIAPI void liArenaTempEnd(LiArenaTemp arena);

#endif // LI_BASE_ARENA_H
