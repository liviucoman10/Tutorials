/* BMPAux implementation */
#include "BMPAux.h"

/* load other useful libraries */
#include <stdio.h>
#include <iostream>

/* setup the static variable */
int BMPAux::bmp_id = 0;

/* implement the constructor */
BMPAux::BMPAux(const char *filename){
	/* create and open file */
	FILE *f = fopen(filename,"rb");

	/* initialize a temporary info array, where we will store the header of the BMP file */
	unsigned char info[BMP_HEAD_SIZE];

	/* read the header data into the info array */
	fread(info, sizeof(unsigned char), BMP_HEAD_SIZE, f);

	/* get the width and height from the header of the BMP file*/
	width = *(int*)&info[BMP_HEAD_WLOC];
	height = *(int*)&info[BMP_HEAD_HLOC];

	/* init the tmp_data array */
	int tmp_size = BMP_COLOR_CMP*width*height;
	unsigned char *tmp_data = new unsigned char[tmp_size];
	fread(tmp_data, sizeof(unsigned char), tmp_size, f);

	/* init the data array */
	int size = width*height;
	data = new rgb_color[size];

	/* order the data bytes into RGB pattern */
	int t = 0;
	for(int i = 0; i < tmp_size; i += BMP_COLOR_CMP){
		data[t].red = tmp_data[i];
		data[t].green = tmp_data[i+2];
		data[t].blue = tmp_data[i+1];
		data[t].t_val = 1;
		t++;
	}

	/* delete tmp data */
	delete[] tmp_data;
	/* close the file */
	fclose(f);

	/* increment the BMP id */
	bmp_id++;
	std::cout << "Initializing image " << bmp_id << " with file: " << filename <<  " (" << width <<"x"<<height<<" px)\n";
}

/* implement the destructor */
BMPAux::~BMPAux(){
	/* make the width and height 0 */
	width = 0;
	height = 0;
	/* delete data, no need to make the pointer nil */
	delete[] data;

	std::cout << "Release memory for image " << bmp_id << "\n";
}

/* implement setters and getters */
int BMPAux::getHeight(){
	return height;
}

int BMPAux::getWidth(){
	return width;
}

rgb_color BMPAux::getPixel(int col, int row){
	return data[col*3 + row*width*4];
}



