#define _USE_MATH_DEFINES  // for M_PI
#include "render_sphere.h"
#include "ReadOBJ.h"
#include <cmath>
#include <math.h> 

vec3 cast_ray(const vec3& orig, const vec3& dir, const Sphere& sphere) {
	float sphere_dist = std::numeric_limits<float>::max();
	if (!sphere.ray_intersect(orig, dir, sphere_dist)) {
		return vec3(0.2, 0.7, 0.8); // background color
	}
	return vec3(0.4, 0.4, 0.3);
}

void render(const Sphere &sphere) {
	const int width = 1024;
	const int height = 768;
	const int fov = M_PI / 2.;
	std::vector<std::vector<vec3>> framebuffer (height, vector<vec3>(width));
	#pragma omp parallel for
	for (size_t j = 0; j < height; j++) {
		for (size_t i = 0; i < width; i++) {
			float x = (2 * (i + 0.5) / (float)width - 1) * tan(fov / 2.) * width / (float)height;
			float y = -(2 * (j + 0.5) / (float)height - 1) * tan(fov / 2.);
			vec3 dir = glm::normalize(vec3(x, y, -1));
			framebuffer[j][i] = cast_ray(vec3(0, 0, 0), dir, sphere);
		}
	}
	image im;
	im.arr = framebuffer;
	im.save();
}