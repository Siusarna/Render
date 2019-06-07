#define _USE_MATH_DEFINES  // for M_PI
#include "render.h"
#include "ReadOBJ.h"
#include "octTree.h";
#include <cmath>
#include <algorithm>
#include "gtx/norm.hpp"



constexpr float kEpsilon = 1e-8;

bool rayTriangleIntersect(
	const vec3& orig, const vec3& dir,
	const vec3& v0, const vec3& v1, const vec3& v2,
	float& t, float& u, float& v)
{
	vec3 v0v1 = v1 - v0;
	vec3 v0v2 = v2 - v0;
	vec3 pvec = cross(dir,v0v2);
	float det = dot(v0v1,pvec);

	if (det < kEpsilon && det > -kEpsilon) return false;

	float invDet = 1 / det;

	vec3 tvec = orig - v0;
	u = dot(tvec,pvec) * invDet;
	if (u < 0 || u > 1) return false;

	vec3 qvec = cross(tvec,v0v1);
	v = dot(dir,qvec) * invDet;
	if (v < 0 || u + v > 1) return false;

	t = dot(v0v2,qvec) * invDet;

	return true;
}


static const float kInfinity = std::numeric_limits<float>::max();

bool scene_intersect(const vec3& orig, const vec3& dir,Triangle triangle, vec3& hit, vec3& N) {
	float dist_i;
	bool temp = false;
	float t, u, v;
	if (rayTriangleIntersect(orig, dir,triangle.v0, triangle.v1, triangle.v2,t,u,v)) {
		hit = orig + dir * t;
		N = (1 - u - v) * triangle.n0 + u * triangle.n1 + v * triangle.n2;
		temp = true;
	}
	return temp;
}

vec3 castRay(
	const vec3& orig, const vec3& dir,Triangle triangle, std::vector<Light>& lights,
	const Options& options)
{
	vec3 point, N;
	if (!scene_intersect(orig, dir,triangle, point, N)) {
		return options.backgroundColor; // background color	    
	}

	float diffuse_light_intensity = 0;
	float diffuse_light_intensity2 = 0;
	bool shad;
	for (size_t i = 0; i < lights.size(); i++) {
		vec3 light_dir = (point-lights[i].position);
		float r2 = l2Norm(light_dir);
		auto distance = sqrt(r2);
		light_dir.x /= distance; light_dir.y /= distance; light_dir.z /= distance;
		float t, u, v;
		shad = !rayTriangleIntersect(point + N * options.bias, -light_dir, triangle.v0, triangle.v1, triangle.v2, t, u, v);
		diffuse_light_intensity += shad*lights[i].intensity * std::max(0.f,  dot(N,light_dir));
		diffuse_light_intensity2 += shad*lights[i].intensity * std::max(0.f, dot(N, -light_dir));
	}
    if (diffuse_light_intensity ==  0) return vec3(0.4, 0.4, 0.7)* diffuse_light_intensity2;
	if (diffuse_light_intensity2 == 0) return vec3(0.4, 0.4, 0.7) * diffuse_light_intensity;
	return vec3(0.4, 0.4, 0.7) *std::min(diffuse_light_intensity,diffuse_light_intensity2);
}


void render(std::vector<Triangle> triangles, std::vector<Light>& lights, Options options, float max) {

	std::vector<std::vector<vec3>> framebuffer (options.height, std::vector<vec3>(options.width,options.backgroundColor));
	octree tree(max, triangles);
	for (size_t j = 0; j < options.height; j++) {
		for (size_t i = 0; i < options.width; i++) {
			float x = (2 * (i + 0.5) / (float)options.width - 1) * tan(options.fov / 2.) * options.width / (float)options.height;
			float z = -(2 * (j + 0.5) / (float)options.height - 1) * tan(options.fov / 2.);
			vec3 dir = glm::normalize(vec3(x, -1, z));
			if (framebuffer[j][i] == options.backgroundColor) {
				std::vector<Triangle> temp;
				tree.findIntersections(options.camera_pos, dir, temp);
				for (int k = 0; k < temp.size(); k++) {
					//vec3 a = castRay(options.camera_pos, dir, temp[k], lights, options);
					vec3 a = castRay(options.camera_pos, dir, temp[k], lights, options);
					if (a != options.backgroundColor) {
						framebuffer[j][i] = a;
						break;
					}
				}
			}
		}
	}
	image im;
	im.arr = framebuffer;
	im.save();
}
