#include "platform/platform_filesystem.h"
#include "base/base_logging.h"

#include <stdio.h>

char *liFileRead(LiArena *arena, const char *filepath)
{
	FILE *fp = fopen(filepath, "rb");
	if (!fp) {
		liLogError("Cannot open file '%s'\n", filepath);
		return NULL;
	}
	// Get file length.
	fseek(fp, 0, SEEK_END);
	U64 len = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	// Create a buffer.
	char *buffer = liArenaPush(arena, len + 1);
	// Read the file contents
	fread(buffer, len, 1, fp);
	fclose(fp);
	// Append a null terminator because it's a string.
	buffer[len] = '\0';
	
	return buffer;
}

void liFileWrite(const char *filepath, const char *content, U64 content_length, LiFileWriteMode write_mode)
{
	char *write_type = NULL;
	switch (write_mode) {
		case LI_FILE_WRITE_MODE_BINARY:
			write_type = "wb";
			break;
		case LI_FILE_WRITE_MODE_NORMAL:
			write_type = "w";
			break;
	}
	FILE *fp = fopen(filepath, write_type);
	if (!fp) {
		liLogError("Cannot create file '%s'\n", filepath);
		return;
	}
	fwrite(content, content_length, 1, fp);
	fclose(fp);
}

void liFileCreate(const char *filepath)
{
	FILE *fp = fopen(filepath, "wb");
	if (!fp) {
		liLogError("Cannot create file '%s'\n", filepath);
		return;
	}
	fclose(fp);
}

void liFileAppend(const char *filepath, const char *content, U64 content_length)
{
	FILE *fp = fopen(filepath, "ab");
	if (!fp) {
		liLogError("Cannot open file '%s'\n", filepath);
		return;
	}
}

B8 liFileExists(const char *filepath)
{
	FILE *fp = fopen(filepath, "rb");
	if (fp) {
		fclose(fp);
		return true;
	}
	return false;
}
