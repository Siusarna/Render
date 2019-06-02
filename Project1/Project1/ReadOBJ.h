#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vec3.hpp>
#include <vec2.hpp>

using namespace std;
struct elem
{
	int vertex;
	int normal;
};

bool loadOBJ(
	const char* path,
	std::vector < glm::vec3 >& out_vertices,
	std::vector < glm::vec3 >& out_normals,
	std::vector< std::vector < elem >>& out_f
);