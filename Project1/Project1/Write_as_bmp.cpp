#include "ReadOBJ.h"
#include <limits>
#include <cmath>
#include <algorithm>



void imageSaver::save(image img) {
	

	FILE* f1;
	f1 = fopen("bmp.bmp", "rb");
	fread(&img.info, sizeof(img.info), 1, f1);
	fclose(f1);

	int padding = 0;
	img.info.width = img.arr[0].size();
	img.info.depth = img.arr.size();
	if ((img.info.width * 3) % 4) padding = 4 - (img.info.width * 3) % 4;
	img.padding = padding;
	img.info.biSizeImage = (img.info.depth * img.info.width * 3) + (padding * img.info.width);
	img.info.filesize = img.info.biSizeImage + sizeof(BMPHEAD);

	FILE* f2;
	f2 = fopen("result.bmp", "wb");
	int8_t d = 0xFF;
	fwrite(&img.info, sizeof(img.info), 1, f2);
	reverse(img.arr.begin(), img.arr.end());

	for (int i = 0; i < img.info.depth; i++) {
		for (int j = 0; j < img.info.width; j++) {
			int8_t color = 255 * std::max(0.f, std::min(1.f,  img.arr[i][j].x));
			fwrite((char*)&color, 1, sizeof(color), f2);
			color = 255 * std::max(0.f, std::min(1.f, img.arr[i][j].y));
			fwrite((char*)& color, 1, sizeof(color), f2);
			color = 255 * std::max(0.f, std::min(1.f, img.arr[i][j].z));
			fwrite((char*)& color, 1, sizeof(color), f2);
		}
		if (img.padding != 0) {
			int p = 0;
			while (p < img.padding) {
				fwrite(&d, 1, 1, f2);
				p++;
			}
		}
	}
	fclose(f2);
}