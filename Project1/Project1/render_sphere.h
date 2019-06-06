#pragma once
#include <vector>
#include <glm.hpp>
using namespace ::glm;

struct elem
{
	int vertex;
	int normal;
};

struct Object
{
	std::vector<vec3> vertices;
	std::vector<vec3> normals;
	std::vector<std::vector<elem>> f;
	Object(std::vector<vec3> vero, std::vector<vec3> norm, std::vector<std::vector<elem>> func) : vertices(vero), normals(norm), f(func) {};
};

struct Light {
	vec3 position;
	float intensity;
	Light(const vec3& p, const float& i) : position(p), intensity(i) {};
	
};
void render(Object obj);