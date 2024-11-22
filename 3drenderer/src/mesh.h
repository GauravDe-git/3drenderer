#pragma once
#include "vector.h"
#include "triangle.h"

#define N_MESH_VERTICES 8
extern Vec3 g_meshVertices[N_MESH_VERTICES];

#define N_MESH_FACES ( 6 * 2 ) // 6 cube faces, 2 triangles per face
extern Face g_meshFaces[N_MESH_FACES];