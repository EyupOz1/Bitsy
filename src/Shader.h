#pragma once

#include "raylib.h"
#include "rlights.h"
#include "rcamera.h"
#include "raymath.h"

void shader_init(Shader* shader, Light* light, Texture2D* tex);