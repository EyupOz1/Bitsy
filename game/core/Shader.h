#pragma once

#include "raylib.h"
#include "rlights.h"
#include "rcamera.h"
#include "raymath.h"
#include "GLOBAL.h"

void shader_init(Shader* shader, Light* light);
void shader_update(Shader* shader, Light *light, Vector3 pos);