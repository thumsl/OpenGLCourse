#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include "linmath.h"

bool readFile(char **s, const char *filename);

void vec3_copy(vec3 dest, vec3 source);

#endif // UTILS_H
