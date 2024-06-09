#include "raylib.h"
#include "raymath.h"


// Most of the Lighting code is from https://github.com/raysan5/raylib/blob/master/examples/shaders/shaders_basic_lighting.c

class Light
{
private:
    /* data */
public:
    int type;
    bool enabled;
    Vector3 position;
    Vector3 target;
    Color color;
    float attenuation;

    // Shader locations
    int enabledLoc;
    int typeLoc;
    int positionLoc;
    int targetLoc;
    int colorLoc;
    int attenuationLoc;

    Light(int type, Vector3 position, Vector3 target, Color color, Shader shader); 
    Light();
    void Update();
};


typedef enum {
    LIGHT_DIRECTIONAL = 0,
    LIGHT_POINT
} LightType;