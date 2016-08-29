#ifndef ENGINE_H
#define ENGINE_H

#include <math.h>
#include <stdbool.h>
#include "camera.h"
#include "light.h"
#include "linmath.h"
#include "mesh.h"
#include "player.h"
#include "shader.h"
#include "window.h"

#define PI acos(-1.0)
#define MOUSE_SENSITIVITY 0.001f
#define WIDTH 800
#define HEIGHT 600

bool initOpenGL();

#endif // ENGINE_H
