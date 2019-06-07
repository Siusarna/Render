#include "ReadOBJ.h"
#include <limits>
#include <cmath>
#include <algorithm>



void image::save() {
	FILE* f1;
	f1 = fopen("bmp.bmp", "rb");
	fread(&this->info, sizeof(this->info), 1, f1);
	fclose(f1);

	int padding=0;
	this->info.width = this->arr[0].size();
	this->info.depth = this->arr.size();
	if ((this->info.width * 3) % 4) padding = 4 - (this->info.width * 3) % 4;
	this->padding = padding;
	this->info.biSizeImage = (this->info.depth * this->info.width * 3) + (padding * this->info.width);
	this->info.filesize = this->info.biSizeImage + sizeof(BMPHEAD);

	FILE* f2;
	f2 = fopen("result.bmp", "wb");
	int8_t d = 0xFF;
	fwrite(&this->info, sizeof(this->info), 1, f2);
	reverse(this->arr.begin(), this->arr.end());
	for (int i = 0; i < this->info.depth; i++) {
		for (int j = 0; j < this->info.width; j++) {
			int8_t temp = 255 * std::max(0.f, std::min(1.f, this->arr[i][j].x));
			fwrite((char*)&temp, 1, sizeof(temp), f2);
			temp = 255 * std::max(0.f, std::min(1.f, this->arr[i][j].y));
			fwrite((char*)& temp, 1, sizeof(temp), f2);
			temp = 255 * std::max(0.f, std::min(1.f, this->arr[i][j].z));
			fwrite((char*)& temp, 1, sizeof(temp), f2);
		}
		if (this->padding != 0) {
			int p = 0;
			while (p < this->padding) {
				fwrite(&d, 1, 1, f2);
				p++;
			}
		}
	}
	fclose(f2);
}