#include "raylib.h"
#include "Core/State.hpp"
#include "Light.hpp"

static int lightsCount = 0;

Light::Light(){}

Light::Light(int type, Vector3 position, Vector3 target, Color color, Shader shader)
{

    if (lightsCount < 4)
    {
        this->enabled = true;
        this->type = type;
        this->position = position;
        this->target = target;
        this->color = color;

        // NOTE: Lighting shader naming must be the provided ones
        this->enabledLoc = GetShaderLocation(shader, TextFormat("lights[%i].enabled", lightsCount));
        this->typeLoc = GetShaderLocation(shader, TextFormat("lights[%i].type", lightsCount));
        this->positionLoc = GetShaderLocation(shader, TextFormat("lights[%i].position", lightsCount));
        this->targetLoc = GetShaderLocation(shader, TextFormat("lights[%i].target", lightsCount));
        this->colorLoc = GetShaderLocation(shader, TextFormat("lights[%i].color", lightsCount));

        this->Update();

        lightsCount++;
    }
}
void Light::Update()
{
    SetShaderValue(State::get().shader, this->enabledLoc, &this->enabled, SHADER_UNIFORM_INT);
    SetShaderValue(State::get().shader, this->typeLoc, &this->type, SHADER_UNIFORM_INT);

    // Send to shader light position values
    float position[3] = {this->position.x, this->position.y, this->position.z};
    SetShaderValue(State::get().shader, this->positionLoc, position, SHADER_UNIFORM_VEC3);

    // Send to shader light target position values
    float target[3] = {this->target.x, this->target.y, this->target.z};
    SetShaderValue(State::get().shader, this->targetLoc, target, SHADER_UNIFORM_VEC3);

    // Send to shader light color values
    float color[4] = {(float)this->color.r / (float)255, (float)this->color.g / (float)255,
                      (float)this->color.b / (float)255, (float)this->color.a / (float)255};
    SetShaderValue(State::get().shader, this->colorLoc, color, SHADER_UNIFORM_VEC4);
}