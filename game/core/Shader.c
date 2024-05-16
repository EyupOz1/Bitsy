#include "Shader.h"

void shader_init(Shader *shader, Light *light)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    *shader = LoadShader(PATH_SHADERS_VERTEX, PATH_SHADERS_FRAGMENT);
    shader->locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(*shader, "viewPos");

    int ambientLoc = GetShaderLocation(*shader, "ambient");
    SetShaderValue(*shader, ambientLoc, (float[4]){0.1f, 0.1f, 0.1f, 1.0f}, SHADER_UNIFORM_VEC4);

    *light = CreateLight(LIGHT_POINT, (Vector3){-2, 1, -2}, Vector3Zero(), (Color){255, 255, 255, 255}, *shader);
}

void shader_update(Shader *shader, Light *light, Vector3 pos)
{
    light->position = pos;
    float cameraPos[3] = {pos.x, pos.y, pos.z};
    SetShaderValue(*shader, shader->locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
    UpdateLightValues(*shader, *light);
}