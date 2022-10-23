#ifndef LI_BASE_STRING_H
#define LI_BASE_STRING_H

#include "base/base_defines.h"
#include "base/base_types.h"
#include "base/base_arena.h"

typedef struct {
	char *c_str;
	U64 length;
} LiString;

LIAPI LiString liString(LiArena *arena, const char *c_str);
LIAPI LiString liStringSub(LiArena *arena, const char *c_str, U32 start, U32 end);

#endif // LI_BASE_STRING_H
