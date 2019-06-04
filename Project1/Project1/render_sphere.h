#pragma once
#include <vector>
#include <glm.hpp>
using namespace ::glm;

struct elem
{
	int vertex;
	int normal;
};

struct Sphere
{
	vec3 center;
	float radius;

	Sphere(const vec3& c, const float& r) : center(c), radius(r) {}
	bool ray_intersect(const vec3& orig, const vec3& dir, float& t0) const {
		vec3 L = center - orig;
		float tca = dot(L,dir);
		float d2 = dot(L,L) - dot(tca,tca);
		if (d2 > radius * radius) return false;
		float thc = sqrtf(dot(radius,radius) - d2);
		t0 = tca - thc;
		float t1 = tca + thc;
		if (t0 < 0) t0 = t1;
		if (t0 < 0) return false;
		return true;
	}
};
void render(std::vector<vec3>vertices, std::vector<vec3> normals, std::vector<std::vector<elem>> f);