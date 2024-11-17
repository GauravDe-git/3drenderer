#include "vector.h"
#include "math.h"

// TODO: Implementation of all Vector functions

Vec3 vec3RotateX(Vec3 v, float angle) {
    Vec3 rotatedVec = {
    .x = v.x,
    .y = v.y * cosf(angle) - v.z * sinf(angle),
    .z = v.y * sinf(angle) + v.z * cosf(angle)};
    return rotatedVec;
}

Vec3 vec3RotateY(Vec3 v, float angle) {
    Vec3 rotatedVec = {
    .x = v.x * cosf(angle) - v.z * sinf(angle),
    .y = v.y,
    .z = v.x * sinf(angle) + v.z * cosf(angle)};
    return rotatedVec;
}
Vec3 vec3RotateZ(Vec3 v, float angle) {
    Vec3 rotatedVec = {
    .x = v.x * cosf(angle) - v.y * sinf(angle),
    .y = v.x * sinf(angle) + v.y * cosf(angle),
    .z = v.z };
    return rotatedVec;
}