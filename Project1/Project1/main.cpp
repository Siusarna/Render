#include <iostream>
#include "ReadOBJ.h"
#include "render_sphere.h"
using namespace std;



int main(int argc, char* argv[]) {

	// Read our .obj file
	vector<vec3> vertices;
	vector<vec3> normals; // Won't be used at the moment.
	vector<vector<elem>> f;
	bool res = loadOBJ("2.obj", vertices, normals,f);
	Object obj(vertices, normals, f);
	render(obj);

	system("pause");
	return 0;
}
	