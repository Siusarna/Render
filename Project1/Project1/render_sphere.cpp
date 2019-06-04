#define _USE_MATH_DEFINES  // for M_PI
#include "render_sphere.h"
#include "ReadOBJ.h"
#include <cmath>
#include <math.h> 

//vec3 cast_ray(const vec3& orig, const vec3& dir, const Sphere& sphere) {
//	float sphere_dist = std::numeric_limits<float>::max();
//	if (!sphere.ray_intersect(orig, dir, sphere_dist)) {
//		return vec3(0.2, 0.7, 0.8); // background color
//	}
//	return vec3(0.4, 0.4, 0.3);
//}

vec3
triangle_intersection(const vec3& orig,
	const vec3& dir,
	const vec3& v0,
	const vec3& v1,
	const vec3& v2) {
	vec3 e1 = v1 - v0;
	vec3 e2 = v2 - v0;
	// Вычисление вектора нормали к плоскости
	vec3 pvec = cross(dir, e2);
	float det = dot(e1, pvec);

	// Луч параллелен плоскости
	if (det < 1e-8 && det > -1e-8) {
		return vec3(1,0,1);
	}

	float inv_det = 1 / det;
	vec3 tvec = orig - v0;
	float u = dot(tvec, pvec) * inv_det;
	if (u < 0 || u > 1) {
		return  vec3(1, 0, 1);
	}

	vec3 qvec = cross(tvec, e1);
	float v = dot(dir, qvec) * inv_det;
	if (v < 0 || u + v > 1) {
		return  vec3(1, 0, 1);
	}
	return vec3(0, 1, 0);
}



void render(vector<vec3>vertices, vector<vec3> normals, vector<vector<elem>> f) {
	const int width = 1024;
	const int height = 768;
	float fov = 150;

	std::vector<std::vector<vec3>> framebuffer (height, vector<vec3>(width));
	for (int k = 0; k < f.size(); k++) {
		for (size_t j = 0; j < height; j++) {
			for (size_t i = 0; i < width; i++) {
				float x = (2 * (i + 0.5) / (float)width - 1) * tan(fov / 2.) * width / (float)height;
				float y = -(2 * (j + 0.5) / (float)height - 1) * tan(fov / 2.);
				vec3 dir = glm::normalize(vec3(x, y, -1));
				float t, u, v;
				framebuffer[j][i] = triangle_intersection(vec3(1, 1, 5), dir, vertices[f[k][0].vertex], vertices[f[k][1].vertex], vertices[f[k][2].vertex]);
			}
		}
	}
	image im;
	im.arr = framebuffer;
	im.save();
}
