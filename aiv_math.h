#include <math.h>

typedef struct Vector3
{
    float x;
    float y;
    float z;
} Vector3_t;

Vector3_t Vector3_new(float x, float y, float z);

Vector3_t Vector3_zero();

Vector3_t screentopixel(float x, float y, int height, int width);

Vector3_t pixeltoscreen(float x, float y, int height, int width);