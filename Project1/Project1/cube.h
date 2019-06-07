#pragma once
#include <vector>
#include "render.h"

class cube
{
public:
	vec3 x1, x2, x3, x4, x5, x6, x7, x8;
	std::vector<Triangle> sides;

	cube() {}
	cube(vec3 x, vec3 y, vec3 z, vec3 k, vec3 x1, vec3 y1, vec3 z1, vec3 k1);

	bool ThereIsIntersectionBetweenRayAndTriangle(vec3 rayOrigin, vec3 rayVector, Triangle inTriangle);
	bool IntersectionBetweetRayAndCube(vec3 rayOrigin, vec3 rayVector);
};