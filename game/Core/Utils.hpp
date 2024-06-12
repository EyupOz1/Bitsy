#include "raylib.h"

#define ExpandVc3(vec) vec.x, vec.y, vec.z

float roundToChunk(float pos);
int map(int input, int in_min, int in_max, int out_min, int out_max);
void getBaseNormals(float* inpt);
void calculateVertices(float *inpt, Vector3 &currPos);
unsigned char Vector3Compare(Vector3 a, Vector3 b);