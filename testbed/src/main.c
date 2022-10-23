#include <lithium.h>

#include <stdio.h>

int main(void)
{
	LiArena *arena = liArenaCreate(liGigabytes(4), 8);
	LiString str = liString(arena, "Cum");
	LiString str2 = liStringSub(arena, "012345", 1, 3);

	printf("'%s', %llu\n", str2.c_str, str2.length);

	liArenaDestroy(arena);
	return 0;
}
