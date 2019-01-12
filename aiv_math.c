#include "aiv_math.h"

Vector3_t Vector3_new(float x, float y, float z)
{
    Vector3_t vector3 = {.x = x, .y = y, .z = z};
    return vector3;
}

Vector3_t Vector3_zero()
{
    Vector3_t vector3 = {0, 0, 0};
    return vector3;
}

Vector3_t screentopixel(float x, float y, int height, int width)
{
    Vector3_t vector3;

    vector3.x = (x / (width / 2)) - 1;
    vector3.y = (y / (height / 2)) - 1;

    if (vector3.x > 1)
    {
        vector3.x = 1;
    }
    else if (vector3.x < -1)
    {
        vector3.x = -1;
    }

    if (vector3.y > 1)
    {
        vector3.y = 1;
    }
    else if (vector3.y < -1)
    {
        vector3.y = -1;
    }

    return vector3;
}

Vector3_t pixeltoscreen(float x, float y, int height, int width)
{
    Vector3_t vector3;

    //vector3.x = ((x + 1) / 2) * width;
    vector3.x = width * (x + 1) / 2;
    vector3.y = height - (height * (y + 1) / 2);

    return vector3;
}