#include "cube.h"

cube::cube(vec3 x, vec3 y, vec3 z, vec3 k, vec3 n1, vec3 y1, vec3 z1, vec3 k1)
{
	this->x1 = x;
	this->x2 = y;
	this->x3 = z;
	this->x4 = k;

	this->x5 = n1;
	this->x6 = y1;
	this->x7 = z1;
	this->x8 = k1;

	vec3 temp(0, 0, 0);
	sides.push_back(Triangle(x7, x6, x8,temp, temp, temp ));
	sides.push_back(Triangle(x5, x6, x8, temp, temp, temp));

	sides.push_back(Triangle(x1, x5, x8, temp, temp, temp));
	sides.push_back(Triangle(x1, x4, x8, temp, temp, temp));

	sides.push_back(Triangle(x5, x2, x6, temp, temp, temp));
	sides.push_back(Triangle(x5, x2, x1, temp, temp, temp));

	sides.push_back(Triangle(x7, x2, x3, temp, temp, temp));
	sides.push_back(Triangle(x7, x2, x6, temp, temp, temp));

	sides.push_back(Triangle(x3, x7, x8, temp, temp, temp));
	sides.push_back(Triangle(x3, x4, x8, temp, temp, temp));

	sides.push_back(Triangle(x3, x2, x4, temp, temp, temp));
	sides.push_back(Triangle(x1, x2, x4, temp, temp, temp));
}

bool cube::ThereIsIntersectionBetweenRayAndTriangle(vec3 rayOrigin, vec3 rayVector, Triangle inTriangle)
{

	vec3 vertex0 = inTriangle.v0;
	vec3 vertex1 = inTriangle.v1;
	vec3 vertex2 = inTriangle.v2;
	vec3 edge1 = vertex1 - vertex0;
	vec3 edge2 = vertex2 - vertex0;
	vec3 h = cross(rayVector,edge2);

	float a = dot(edge1,h);
	float EPSILON = 1e-5f;

	if (a > -EPSILON && a < EPSILON)
	{
		return false;
	}
	float f = 1 / a;
	vec3 s = rayOrigin - vertex0;
	float u = f * dot(s,h);
	if (u < 0.0 || u > 1.0)
	{
		return false;
	}
	vec3 q = cross(s,edge1);
	float v = f * dot(rayVector,q);
	if (v < 0.0 || u + v > 1.0)
	{
		return false;
	}

	// At this stage we can compute t to find out where the intersection point is on the line.
	float t = f * dot(edge2,q);
	return true;
}

bool cube::IntersectionBetweetRayAndCube(vec3 rayOrigin, vec3 rayVector)
{
	for (Triangle i : sides)
	{
		if (ThereIsIntersectionBetweenRayAndTriangle(rayOrigin, rayVector, i))
			return true;
	}
	return false;
}