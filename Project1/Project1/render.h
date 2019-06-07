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

struct Triangle
{
	vec3 v0;
	vec3 v1;
	vec3 v2;
	vec3 n0;
	vec3 n1;
	vec3 n2;
	Triangle(vec3& vv0, vec3& vv1, vec3& vv2, vec3& nn0, vec3& nn1, vec3& nn2) : v0(vv0), v1(vv1), v2(vv2), n0(nn0), n1(nn1), n2(nn2) {};
};

struct Options
{
	vec3 camera_pos = vec3(0, -3, 0);
	uint32_t width = 200;
	uint32_t height = 200;
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

void render(std::vector<Triangle> triangles, std::vector<Light>& lights, Options options, float max);