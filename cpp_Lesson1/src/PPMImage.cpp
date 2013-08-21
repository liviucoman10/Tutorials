/* implement the PPM image class */
#include "PPMImage.h"

/* include classes for file I/O */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

/* create the constructor and destructor */
PPMImage::PPMImage(const char *filename){
//	FILE *fp = fopen(filename, "rb");


	/* declare aux variables */
	char 	buff[16];
	int		c, rgb_comp_color;

	/* first open a file for binary reading */
	FILE *fp;
	if(!(fp = fopen(filename, "rb"))){
		std::cout << "Error opening " << filename << "\n";
	}

	/* read image format */
	if (!fgets(buff, sizeof(buff), fp)) {
		std::cout << "Error reading file format for " << filename << "\n";
	    exit(1);
	}

	/* check the image format */
	if (buff[0] != 'P' || buff[1] != '6') {
		std::cout << "Error! the file format must be P6!\n";
	    exit(1);
	}

	/* check for comments */
	c = getc(fp);
	while (c == '#') {
	    while (getc(fp) != '\n') ;
	         c = getc(fp);
	}

	/* read image size information */
	ungetc(c, fp);
	if (fscanf(fp, "%d %d", &width, &height) != 2) {
		std::cout << "Invalid image size (Error loading " << filename << ")\n";
		exit(1);
	}

	/*	read rgb component */
	if (fscanf(fp, "%d", &rgb_comp_color) != 1) {
		std::cout << "Invalid rgb component (Error loading " << filename << ")\n";
	    exit(1);
	}

	/* check rgb component depth */
	if (rgb_comp_color!= RGB_COMPONENT_COLOR) {
		std::cout << "Error! " << filename << " does not have 8-bits components\n";
	    exit(1);
	}

	/* check out for more new line characters */
	while (fgetc(fp) != '\n') ;
	/* memory allocation for pixel data */
	pixels = new PPMPixel[width*height*sizeof(PPMPixel)];
	if(fread(pixels, PPM_COLOR_FORMAT * width, height, fp)){
		std::cout << "Success! Image " << filename << " loaded OK\n";
	}
	else{
		std::cout << "Error! Image " << filename << " did not load RGB data OK\n";
	}

	/* close the file */
	fclose(fp);
}

PPMImage::~PPMImage(){
	/* reset width and height */
	width = height = 0;
	/* delete the array */
	delete[] pixels;

	std::cout << "Image deleted\n";
}

/* getters and setters */
PPMPixel PPMImage::getPixel(int col, int row){
	return pixels[col*PPM_COLOR_FORMAT + row*PPM_COLOR_FORMAT*width];
}

PPMPixel* PPMImage::getPixels(){
	return pixels;
}

int	PPMImage::getWidth(){
	return width;
}

int	PPMImage::getHeight(){
	return height;
}
