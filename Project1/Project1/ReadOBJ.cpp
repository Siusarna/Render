#include "ReadOBJ.h"



 bool loadOBJ(const char* path, std::vector<Triangle>& triangles) {

	std::vector < glm::vec3 > out_vertices;
	std::vector < glm::vec3 > out_normals;
	std::vector<vector < elem >> out_f;
	FILE* file = fopen(path, "r");
	if (file == nullptr) {
		return false;
	}
	vector<vector<elemtemp>> tem;
	while (1) {

		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break;
		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			out_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			out_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			vector<elemtemp> temp;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0],&normalIndex[0],&vertexIndex[1], &normalIndex[1], &vertexIndex[2], & normalIndex[2] );
			
			for (int i = 0; i < 3; i++) {
				
				elemtemp t;
				t.vertex = vertexIndex[i]-1;
				t.normal = normalIndex[i]-1;
				temp.push_back(t);
			}
			tem.push_back(temp);
			temp.clear();
		}
	}
	vector<elem> a;
	for (int i = 0; i < tem.size(); i++) {
		for (int j = 0; j < tem[i].size(); j++) {
			elem t;
			t.normal = out_normals[tem[i][j].normal];
			t.vertex = out_vertices[tem[i][j].vertex];
			a.push_back(t);
		}
		out_f.push_back(a);
		a.clear();
	}
	for (int i = 0; i < out_f.size(); i++) {
		Triangle temp(out_f[i][0].vertex, out_f[i][1].vertex, out_f[i][2].vertex, out_f[i][0].normal, out_f[i][1].normal, out_f[i][2].normal);
		triangles.push_back(temp);
	}

	return true;
}