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

struct PIXELDATA
{
	int8_t rgbRed;
	int8_t rgbGreen;
	int8_t rgbBlue;
	int8_t rgbReserved;
	PIXELDATA() : rgbBlue(), rgbGreen(), rgbRed() {}
};

class image {
private:	
	vector<vector<PIXELDATA>> arr;
	int padding;
	BMPHEAD info;
public:
	void save(vector<vector<PIXELDATA>> arr, string path);
};

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