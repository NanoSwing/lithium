#ifndef LI_BASE_ARENA_H
#define LI_BASE_ARENA_H

#include "base/base_types.h"
#include "base/base_defines.h"
#include "platform/platform_threading.h"

typedef struct LiArena LiArena;
typedef struct {
	LiArena *arena;
	U64 pos;
} LiArenaTemp;

LIAPI LiArena *liArenaCreate(U64 size, U64 align);
LIAPI void liArenaDestroy(LiArena *arena);

LIAPI void *liArenaPush(LiArena *arena, U64 size);
LIAPI void *liArenaPushZero(LiArena *arena, U64 size);
LIAPI void liArenaPop(LiArena *arena, U64 size);
LIAPI void liArenaReset(LiArena *arena);

LIAPI LiArenaTemp liArenaTempBegin(LiArena *arena);
LIAPI void liArenaTempEnd(LiArenaTemp arena);

#endif // LI_BASE_ARENA_H
