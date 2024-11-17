#pragma once

typedef struct {
    float x;
    float y;
} Vec2;

typedef struct {
    float x;
    float y;
    float z;
} Vec3;

//TODO:  Functions to manipulate vector2d and 3d

Vec3 vec3RotateX(Vec3 v, float angle);
Vec3 vec3RotateY(Vec3 v, float angle);
Vec3 vec3RotateZ(Vec3 v, float angle);