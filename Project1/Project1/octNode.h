#pragma once
#include "render.h"
#include <vector>
#include "cube.h"

class octNode
{
	cube spaceCube;
public:
	bool list = true;
	std::vector<Triangle> triangles;
	octNode** doughterNodes = new octNode * [8];

	octNode(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
	~octNode();
	void rebuild(float min);
	void findIntesections(vec3 rayOrigin, vec3 rayVector, std::vector<Triangle>& result);
	int positionFinder(vec3 x, vec3 center);
};