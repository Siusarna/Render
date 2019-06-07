#include "octTree.h"



octree::octree(float max, std::vector<Triangle> allTriangles)
{
	minSize = max / 10;
	maxSize = max;
	head = new octNode(-max, max, -max, max, -max, max);
	head->triangles = allTriangles;
	head->rebuild(minSize);
}


octree::~octree()
{

}

void octree::findIntersections(vec3 rayOrigin, vec3 rayVector, std::vector<Triangle>& result)
{
	head->findIntesections(rayOrigin, rayVector, result);
}