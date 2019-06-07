#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <glm.hpp>
#include "render.h"
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
	friend void render(std::vector<Triangle> triangles, std::vector<Light>& lights, Options options);
};




class Triangle
{
public:
	Triangle(vec3 vv0, vec3 vv1, vec3 vv2, vec3 nn0, vec3 nn1, vec3 nn2);
	~Triangle();
	vec3 v0;
	vec3 v1;
	vec3 v2;
	vec3 n0;
	vec3 n1;
	vec3 n2;

private:
	
};

Triangle::Triangle(vec3 vv0, vec3 vv1, vec3 vv2, vec3 nn0, vec3 nn1, vec3 nn2)
{
	this->v0 = vv0;
	this->v1 = vv1;
	this->v2 = vv2;
	this->n0 = nn0;
	this->n1 = nn1;
	this->n2 = nn2;
}

Triangle::~Triangle()
{
}
bool loadOBJ(const char* path, std::vector<Triangle>& triangles);