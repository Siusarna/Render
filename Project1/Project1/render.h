#pragma once
#include <vector>
#include "glm.hpp"

using namespace ::glm;

struct elem
{
	vec3 vertex;
	vec3 normal;
};

struct elemtemp
{
	int vertex;
	int normal;
};


struct Options
{
	uint32_t width = 100;
	uint32_t height = 100;
	float fov = 150;
	vec3 backgroundColor = vec3(1,1,1);
	float bias = 0.75;
	uint32_t maxDepth = 5;
};

struct Light {
	Light(const vec3& p, const float& i) : position(p), intensity(i) {}
	vec3 position;
	float intensity;
};

void render(std::vector<Triangle> triangles, std::vector<Light>& lights, Options options);