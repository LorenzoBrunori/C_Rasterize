#include "aiv_rasterizer.h"
#include <string.h>
#include <stdio.h>

Vertex_t Vertex_new(Vector3_t position)
{
    Vertex_t vertex;
    memset(&vertex, 0, sizeof(Vertex_t));
    vertex.position = position;
    return vertex;
}

Triangle_t Triangle_new(Vertex_t a, Vertex_t b, Vertex_t c)
{
    Triangle_t triangle = {.a = a, .b = b, .c = c};
    return triangle;
}

static void put_pixel(Context_t *ctx, int x, int y, int r, int g, int b, int a)
{

    if (x < 0 || y < 0 || x >= ctx->width || y >= ctx->height)
    {
        return;
    }
    int offset = ((y * ctx->width) + x) * 4;

    ctx->framebuffer[offset++] = a;
    ctx->framebuffer[offset++] = b;
    ctx->framebuffer[offset++] = g;
    ctx->framebuffer[offset] = r;
}

static float inversed_slope(float x0, float y0, float x1, float y1)
{
    float res = (x1 - x0) / (y1 - y0);
    printf("res=%f\n", res);
    return res;
}

static float lerp(float start, float end, float gradient)
{
    return start + (end - start) * gradient;
}

void rasterize(Context_t *ctx, Triangle_t *triangle)
{
    Vector3_t vec_a = pixeltoscreen(triangle->a.position.x, triangle->a.position.y, ctx->width, ctx->height);
    triangle->a.raster_x = vec_a.x;
    triangle->a.raster_y = vec_a.y;

    Vector3_t vec_b = pixeltoscreen(triangle->b.position.x, triangle->b.position.y, ctx->width, ctx->height);
    triangle->b.raster_x = vec_b.x;
    triangle->b.raster_y = vec_b.y;

    Vector3_t vec_c = pixeltoscreen(triangle->c.position.x, triangle->c.position.y, ctx->width, ctx->height);
    triangle->c.raster_x = vec_c.x;
    triangle->c.raster_y = vec_c.y;

    Vector3_t ver_array[3];
    ver_array[0] = vec_a;
    ver_array[1] = vec_b;
    ver_array[2] = vec_c;

    int i;
    int j;
    int temp;
    for (i = 0; i < 3 - 1; i++)
    {
        for (j = i + 1; j < 3; j++)
        {

            if (ver_array[i].y > ver_array[j].y)
            {
                temp = ver_array[i].y;
                ver_array[i].y = ver_array[j].y;
                ver_array[j].y = temp;
            }
        }
    }
    printf("[0]%f\n", ver_array[0].y);
    printf("[1]%f\n", ver_array[1].y);
    printf("[2]%f\n", ver_array[2].y);

    float slope1 = inversed_slope(ver_array[0].x, ver_array[0].y, ver_array[1].x, ver_array[1].y);
    float slope2 = inversed_slope(ver_array[0].x, ver_array[0].y, ver_array[2].x, ver_array[1].y);

    int x3;
    for (int y = ver_array[0].y; y < ver_array[1].y; y++)
    {
        float gradient = (float)(y - ver_array[0].y) / (float)(ver_array[1].y - ver_array[0].y);
        float x = lerp(ver_array[0].x, ver_array[1].x, gradient);
        put_pixel(ctx, x, y, 255, 0, 0, 255);

        float gradient2 = (float)(y - ver_array[0].y) / (float)(ver_array[2].y - ver_array[0].y);
        float x2 = lerp(ver_array[0].x, ver_array[2].x, gradient2);
        put_pixel(ctx, x2, y, 255, 0, 0, 255);

        if(slope1 < slope2)
        {
            
            for(x3 = x; x3 < x2; x3++)
            {
                put_pixel(ctx, x3, y, 255, 0, 0, 255);
            }
        }
        else
        {
            for(x3 = x2; x3 < x; x3++)
            {
                put_pixel(ctx, x3, y, 255, 0, 0, 255);
            }
        }
        
    }
    for (int y = ver_array[1].y; y < ver_array[2].y; y++)
    {
        float gradient = (float)(y - ver_array[1].y) / (float)(ver_array[2].y - ver_array[1].y);
        float x = lerp(ver_array[1].x, ver_array[2].x, gradient);
        put_pixel(ctx, x, y, 255, 0, 0, 255);

        float gradient2 = (float)(y - ver_array[2].y) / (float)(ver_array[0].y - ver_array[2].y);
        float x2 = lerp(ver_array[2].x, ver_array[0].x, gradient2);
        put_pixel(ctx, x2, y, 255, 0, 0, 255);

        if(slope1 < slope2)
        {
            
            for(x3 = x; x3 < x2; x3++)
            {
                put_pixel(ctx, x3, y, 255, 0, 0, 255);
            }
        }
        else
        {
            for(x3 = x2; x3 < x; x3++)
            {
                put_pixel(ctx, x3, y, 255, 0, 0, 255);
            }
        }
    }

    if (slope1 < slope2)
    {
        //printf("sinistra");
    }
    if (slope1 > slope2)
    {
        printf("destra");
    }

    put_pixel(ctx, triangle->a.raster_x, triangle->a.raster_y, 255, 255, 0, 255);
    put_pixel(ctx, triangle->b.raster_x, triangle->b.raster_y ,255, 255, 0, 255);
    put_pixel(ctx, triangle->c.raster_x, triangle->c.raster_y, 255, 255, 0, 255);
}

void clear(Context_t *ctx)
{
    memset(ctx->framebuffer, 0, ctx->width * ctx->height * 4);
}
