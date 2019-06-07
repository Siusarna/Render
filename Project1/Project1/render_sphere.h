#pragma once
#include <vector>
#include "glm.hpp"

using namespace ::glm;

struct elem
{
	int vertex;
	int normal;
};

struct Options
{
	uint32_t width = 350;
	uint32_t height = 300;
	float fov = 150;
	vec3 backgroundColor = vec3(1,1,1);
	float bias = 0.0001;
	uint32_t maxDepth = 5;
};

struct Light {
	Light(const vec3& p, const float& i) : position(p), intensity(i) {}
	vec3 position;
	float intensity;
};

void render(std::vector<vec3>vertices, std::vector<vec3> normals, std::vector<std::vector<elem>> f, std::vector<Light>& lights, Options options);