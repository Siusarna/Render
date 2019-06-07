#include <iostream>
#include "ReadOBJ.h"
#include "render.h"
using namespace std;



int main(int argc, char* argv[]) {

	// Read our .obj file
	std::vector<Triangle> triangles;
	bool res = loadOBJ("2.obj", triangles);
	Object obj(vertices,normals,f);
	Options option;
	std::vector<Light>  lights;
	lights.push_back(Light(vec3(0, 0, 3), 1.5));
	render(obj, lights,option);

	system("pause");
	return 0;
}
	