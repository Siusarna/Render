#include "ReadOBJ.h"

void image::save(vector<vector<PIXELDATA>> arr, string path) {
	image im;
	FILE* f1;
	f1 = fopen("bmp.bmp", "rb");
	fread(&im.info, sizeof(im.info), 1, f1);
	fclose(f1);

	int padding;
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
			fwrite((char*)& im.arr[i][j].rgbBlue, 1, 1, f2);
			fwrite((char*)& im.arr[i][j].rgbGreen, 1, 1, f2);
			fwrite((char*)& im.arr[i][j].rgbRed, 1, 1, f2);
		}
		if (im.padding != 0) {
			int p = 0;
			while (p < im.padding) {
				fwrite(&d, 1, 1, f2);
				p++;
			}
		}
	}
}