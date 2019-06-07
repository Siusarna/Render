#include <iostream>
#include "ReadOBJ.h"
#include "render.h"
using namespace std;



int main(int argc, char* argv[]) {

	std::vector<Triangle> triangles;
	bool res = loadOBJ("2.obj", triangles);
	Options option;
	std::vector<Light>  lights;
	lights.push_back(Light(vec3(0, 0, 3), 1.5));
	render(triangles, lights, option);

	system("pause");
	return 0;
}
	