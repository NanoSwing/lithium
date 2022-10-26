#ifndef LI_BASE_STRING_H
#define LI_BASE_STRING_H

#include "base/base_defines.h"
#include "base/base_types.h"
#include "base/base_arena.h"

typedef struct {
	char *c_str;
	U64 length;
} LiString;

LIAPI LiString liString(const char *c_str);
LIAPI LiString liStringPush(LiArena *arena, const char *c_str);

LIAPI LiString liStringSub(LiString string);

#endif // LI_BASE_STRING_H
