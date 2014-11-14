#include "string.h"

void memset(void *src, int val, int size)
{
	if (size < 0)
		return;
	
	char c = (char)val;
	char *tmp = src;
	int i;

	for (i = 0; i < size; i++) {
		tmp[i] = c;
	}
}

char *strcpy(char *dst, const char *src)
{
	char *result = dst;
	while (*src != '\0') {
		*dst = *src;
		dst++;
		src++;
	}

	return result;
}

char *strcat(char *dst, const char *src)
{
	char *tmp = dst;

	while (*tmp != '\0')
		tmp++;

	while (*src != '\0') {
		*tmp = *src;
		tmp++;
		src++;
	}

	return dst;
}
