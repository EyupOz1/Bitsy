#include "raylib.h"
#include "world/Chunk.h"

Vector3 worldPositionToChunk(Vector3 pos);
unsigned char Vector3Compare(Vector3 a, Vector3 b);
int map(int input, int in_min, int in_max, int out_min, int out_max);
int roundToInt(float number);
float floorToInt(float x);