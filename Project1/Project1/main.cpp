#include <iostream>
#include "ReadOBJ.h"
#include "render_sphere.h"
using namespace std;



int main(int argc, char* argv[]) {

	// Read our .obj file
	vector<vec3> vertices;
	vector<vec3> normals; // Won't be used at the moment.
	vector<vector<elem>> f;
	bool res = loadOBJ("cube.obj", vertices, normals,f);
	render(vertices,normals,f);

	system("pause");
	return 0;
}
	