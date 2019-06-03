#include "ReadOBJ.h"
#include <limits>
#include <cmath>
#include <algorithm>



void image::save(vector<vector<glm::vec3>> arr, string path) {
	image im;
	FILE* f1;
	f1 = fopen("bmp.bmp", "rb");
	fread(&im.info, sizeof(im.info), 1, f1);
	fclose(f1);

	int padding=0;
	im.info.width = arr[0].size();
	im.info.depth = arr.size();
	if ((im.info.width * 3) % 4) padding = 4 - (im.info.width * 3) % 4;
	im.padding = padding;
	im.info.biSizeImage = (im.info.depth * im.info.width * 3) + (padding * im.info.width);
	im.info.filesize = im.info.biSizeImage + sizeof(BMPHEAD);

	FILE* f2;
	f2 = fopen("result.bmp", "wb");
	int8_t d = 0xFF;
	fwrite(&im.info, sizeof(im.info), 1, f2);
	for (int i = 0; i < im.info.depth; i++) {
		for (int j = 0; j < im.info.width; j++) {
			int8_t temp = 255 * max(0.f, min(1.f, arr[i][j].x));
			fwrite((char*)&temp, 1, sizeof(temp), f2);
			temp = 255 * max(0.f, min(1.f, arr[i][j].y));
			fwrite((char*)& temp, 1, sizeof(temp), f2);
			temp = 255 * max(0.f, min(1.f, arr[i][j].z));
			fwrite((char*)& temp, 1, sizeof(temp), f2);
		}
		if (im.padding != 0) {
			int p = 0;
			while (p < im.padding) {
				fwrite(&d, 1, 1, f2);
				p++;
			}
		}
	}
	fclose(f2);
}