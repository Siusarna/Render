#include "octNode.h"

octNode::octNode(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
	vec3 x1(maxX, maxY, maxZ);
	vec3 x2(minX, maxY, maxZ);
	vec3 x3(minX, minY, maxZ);
	vec3 x4(maxX, minY, maxZ);

	vec3 x5(maxX, maxY, minZ);
	vec3 x6(minX, maxY, minZ);
	vec3 x7(minX, minY, minZ);
	vec3 x8(maxX, minY, minZ);

	spaceCube = cube(x1, x2, x3, x4, x5, x6, x7, x8);
}

void octNode::rebuild(float min)
{
	float minXnew, maxXnew, minYnew, maxYnew, minZnew, maxZnew;


	// 1, 2, 3, 4 oct
	vec3 center = vec3((spaceCube.x1.x + spaceCube.x2.x) * 0.5, (spaceCube.x1.y + spaceCube.x4.y) * 0.5, (spaceCube.x1.z + spaceCube.x5.z) * 0.5);

	minXnew = (spaceCube.x1.x + spaceCube.x2.x) * 0.5;
	maxXnew = spaceCube.x1.x;
	minYnew = (spaceCube.x1.y + spaceCube.x4.y) * 0.5;
	maxYnew = spaceCube.x1.y;
	minZnew = (spaceCube.x1.z + spaceCube.x5.z) * 0.5;
	maxZnew = spaceCube.x1.z;

	if (triangles.size() < 100 || (maxXnew - minXnew) < min)
		return;

	doughterNodes[0] = new octNode(minXnew, maxXnew, minYnew, maxYnew, minZnew, maxZnew);

	maxXnew = (spaceCube.x1.x + spaceCube.x2.x) * 0.5;
	minXnew = spaceCube.x2.x;
	minYnew = (spaceCube.x1.y + spaceCube.x4.y) * 0.5;
	maxYnew = spaceCube.x1.y;
	minZnew = (spaceCube.x1.z + spaceCube.x5.z) * 0.5;
	maxZnew = spaceCube.x1.z;

	doughterNodes[1] = new octNode(minXnew, maxXnew, minYnew, maxYnew, minZnew, maxZnew);

	maxXnew = (spaceCube.x1.x + spaceCube.x2.x) * 0.5;
	minXnew = spaceCube.x2.x;
	maxYnew = (spaceCube.x2.y + spaceCube.x3.y) * 0.5;
	minYnew = spaceCube.x3.y;
	minZnew = (spaceCube.x1.z + spaceCube.x5.z) * 0.5;
	maxZnew = spaceCube.x1.z;

	doughterNodes[2] = new octNode(minXnew, maxXnew, minYnew, maxYnew, minZnew, maxZnew);

	minXnew = (spaceCube.x3.x + spaceCube.x4.x) * 0.5;
	maxXnew = spaceCube.x4.x;
	maxYnew = (spaceCube.x1.y + spaceCube.x4.y) * 0.5;
	minYnew = spaceCube.x4.y;
	minZnew = (spaceCube.x1.z + spaceCube.x5.z) * 0.5;
	maxZnew = spaceCube.x1.z;

	doughterNodes[3] = new octNode(minXnew, maxXnew, minYnew, maxYnew, minZnew, maxZnew);

	// 5, 6, 7, 8 oct

	minXnew = (spaceCube.x1.x + spaceCube.x2.x) * 0.5;
	maxXnew = spaceCube.x1.x;
	minYnew = (spaceCube.x1.y + spaceCube.x4.y) * 0.5;
	maxYnew = spaceCube.x1.y;
	maxZnew = (spaceCube.x1.z + spaceCube.x5.z) * 0.5;
	minZnew = spaceCube.x5.z;

	doughterNodes[4] = new octNode(minXnew, maxXnew, minYnew, maxYnew, minZnew, maxZnew);

	maxXnew = (spaceCube.x1.x + spaceCube.x2.x) * 0.5;
	minXnew = spaceCube.x2.x;
	minYnew = (spaceCube.x1.y + spaceCube.x4.y) * 0.5;
	maxYnew = spaceCube.x1.y;
	maxZnew = (spaceCube.x1.z + spaceCube.x5.z) * 0.5;
	minZnew = spaceCube.x5.z;

	doughterNodes[5] = new octNode(minXnew, maxXnew, minYnew, maxYnew, minZnew, maxZnew);

	maxXnew = (spaceCube.x1.x + spaceCube.x2.x) * 0.5;
	minXnew = spaceCube.x2.x;
	maxYnew = (spaceCube.x2.y + spaceCube.x3.y) * 0.5;
	minYnew = spaceCube.x3.y;
	maxZnew = (spaceCube.x1.z + spaceCube.x5.z) * 0.5;
	minZnew = spaceCube.x5.z;

	doughterNodes[6] = new octNode(minXnew, maxXnew, minYnew, maxYnew, minZnew, maxZnew);

	minXnew = (spaceCube.x3.x + spaceCube.x4.x) * 0.5;
	maxXnew = spaceCube.x4.x;
	maxYnew = (spaceCube.x1.y + spaceCube.x4.y) * 0.5;
	minYnew = spaceCube.x4.y;
	maxZnew = (spaceCube.x1.z + spaceCube.x5.z) * 0.5;
	minZnew = spaceCube.x5.z;

	doughterNodes[7] = new octNode(minXnew, maxXnew, minYnew, maxYnew, minZnew, maxZnew);

	std::vector<Triangle> newVectors;

	while (!triangles.empty())
	{
		int counter1 = -1;
		int counter2 = -1;
		int counter3 = -1;

		Triangle i = triangles.back();
		triangles.pop_back();

		counter1 = positionFinder(i.v0, center);
		counter2 = positionFinder(i.v1, center);
		counter3 = positionFinder(i.v2, center);

		if (counter1 == counter2 && counter2 == counter3)
			doughterNodes[counter1]->triangles.push_back(i);
		else
			newVectors.push_back(i);
	}

	triangles = newVectors;

	list = false;

	doughterNodes[0]->list = true;
	doughterNodes[0]->rebuild(min);
	doughterNodes[1]->list = true;
	doughterNodes[1]->rebuild(min);
	doughterNodes[2]->list = true;
	doughterNodes[2]->rebuild(min);
	doughterNodes[3]->list = true;
	doughterNodes[3]->rebuild(min);
	doughterNodes[4]->list = true;
	doughterNodes[4]->rebuild(min);
	doughterNodes[5]->list = true;
	doughterNodes[5]->rebuild(min);
	doughterNodes[6]->list = true;
	doughterNodes[6]->rebuild(min);
	doughterNodes[7]->list = true;
	doughterNodes[7]->rebuild(min);
}

void octNode::findIntesections(vec3 rayOrigin, vec3 rayVector, std::vector<Triangle>& result)
{

	for (Triangle i : triangles)
		result.push_back(i);
	if (list)
		return;

	for (int i = 0; i < 8; i++)
	{
		if (doughterNodes[i] && doughterNodes[i]->spaceCube.IntersectionBetweetRayAndCube(rayOrigin, rayVector))
		{
			doughterNodes[i]->findIntesections(rayOrigin, rayVector, result);
		}
	}

}

int octNode::positionFinder(vec3 x, vec3 center)
{
	if (x.z > center.z)
	{
		if (x.y > center.y)
		{
			if (x.x > center.x)
				return 0;
			else
				return 1;
		}
		else
		{
			if (x.x > center.x)
				return 3;
			else
				return 2;
		}
	}
	else
	{
		if (x.y > center.y)
		{
			if (x.x > center.x)
				return 4;
			else
				return 5;
		}
		else
		{
			if (x.x > center.x)
				return 7;
			else
				return 6;
		}
	}
}

octNode::~octNode(){
	for(int i = 0; i < 8; i++){
		delete doughterNodes[i];
	}
	delete[] doughterNodes;
}