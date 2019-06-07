#pragma once
#include "render.h"
#include <vector>
#include "octNode.h"
#include "cube.h"

class octree
{
	float maxSize;
	float minSize;
	octNode* head;
public:
	octree(float max, std::vector<Triangle> allTriangles);
	void findIntersections(vec3 rayOrigin, vec3 rayVector, std::vector<Triangle>& result);
	~octree();
};