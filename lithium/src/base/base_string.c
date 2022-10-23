#include "base/base_string.h"
#include "base/base_arena.h"

#include <string.h>

LiString liString(LiArena *arena, const char *c_str)
{
	LiString str;
	str.length = strlen(c_str);
	str.c_str = liArenaPush(arena, str.length);
	strncpy(str.c_str, c_str, str.length);
	return str;
}

LiString liStringSub(LiArena *arena, const char *c_str, U32 start, U32 end)
{
	LiString str;
	str.length = end - start + 1;
	str.c_str = liArenaPush(arena, str.length + 1);
	for (U32 i = 0; i < str.length; i++) {
		str.c_str[i] = c_str[start + i];
	}
	str.c_str[str.length] = '\0';
	return str;
}
