#include <iostream>
#include "ReadOBJ.h"
#include "render.h"
using namespace std;



int main(int argc, char* argv[]) {

	std::vector<Triangle> triangles;
	float max = 0;
	bool res = loadOBJ("2.obj", triangles, max);
	Options option;
	std::vector<Light>  lights;
	lights.push_back(Light(vec3(0, 0, 4), 0.75));
	renderer rend;
	rend.render(triangles, lights, option, max);

	system("pause");
	return 0;
}
	