#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <glm.hpp>
#include "render_sphere.h"
using namespace std;
using namespace glm;



#pragma pack(2)
typedef struct {
	int8_t  id[2];
	int32_t filesize;
	int16_t reserved[2];
	int32_t headersize;
	int32_t infoSize;
	int32_t width;
	int32_t depth;
	int16_t biPlanes;
	int16_t bits;
	int32_t biCompression;
	int32_t biSizeImage;
	int32_t biXPelsPerMeter;
	int32_t biYPelsPerMeter;
	int32_t biClrUsed;
	int32_t biClrImportant;
} BMPHEAD;




class image {
private:	
	vector<vector<vec3>> arr;
	int padding;
	BMPHEAD info;
public:
	void save();
	friend void render(Object obj);
};


bool loadOBJ(
	const char* path,
	std::vector < vec3 >& out_vertices,
	std::vector < vec3 >& out_normals,
	std::vector< vector < elem >>& out_f
);