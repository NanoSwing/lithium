#include "base/base_string.h"
#include "base/base_arena.h"

#include <string.h>

LiString liString(char *c_str)
{
	LiString str;
	str.c_str = c_str;
	str.length = strlen(c_str);
	return str;
}

LiString liStringPush(LiArena *arena, const char *c_str)
{
	LiString str;
	str.length = strlen(c_str);
	str.c_str = liArenaPush(arena, str.length);
	memcpy(str.c_str, c_str, str.length);
	return str;
}
