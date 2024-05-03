#include "raylib.h"

#define MAX_CHAR_COUNT 40

typedef struct
{
    Rectangle pos;
    char text[MAX_CHAR_COUNT];
    int letterCount;
    unsigned char isVisible;

} Text;


void Text_collision(Text *text);
Text text_create(float x, float y, float width, float height);
void Text_draw(Text *text);