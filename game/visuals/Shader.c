#include "Shader.h"

void shader_init()
{
    
    GLOBAL.shader = LoadShader(PATH_SHADERS_VERTEX, PATH_SHADERS_FRAGMENT);
    GLOBAL.shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(GLOBAL.shader, "viewPos");

    int ambientLoc = GetShaderLocation(GLOBAL.shader, "ambient");
    SetShaderValue(GLOBAL.shader, ambientLoc, (float[4]){0.1f, 0.1f, 0.1f, 1.0f}, SHADER_UNIFORM_VEC4);

}
