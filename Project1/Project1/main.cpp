#include <iostream>
#include "ReadOBJ.h"
#include "render_sphere.h"
using namespace std;



int main(int argc, char* argv[]) {

	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals; // Won't be used at the moment.
	vector<vector<elem>> f;
	//bool res = loadOBJ("cube.obj", vertices, normals,f);
	Sphere sphere(vec3(-3, 0, -16), 2);
	render(sphere);

	system("pause");
	return 0;
}
	