#include "utils.h"
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

bool readFile(char **s, const char *filename) {
	struct stat st;
	int i;

	if (stat(filename, &st) == -1)
		return false;

	*s = malloc((st.st_size+1) * sizeof(char));
	memset(*s, 0, st.st_size+1);

	FILE *f;
	f = fopen(filename, "rb");
	fread(*s, 1, st.st_size, f);

	return true;
}
