/* PPM Image implementation */
#include "PPMImage.h"

/* include headers for file manip */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

/* init class static variables */
int PPMImage::simg_id = 0;

PPMImage::PPMImage(const char *filename){
	/* first message */
	std::cout<<"\n[Img "<<simg_id<<" Constructor] -------------------\n";
	img_id = simg_id;
	simg_id++;

	/* get the file */
	FILE *fp;
	if(!(fp = fopen(filename, "rb"))){
		std::cout<<"[Error] Error reading file "<<filename<<"\n";
	}
	else{
		std::cout<<"[OK] File "<<filename<<" read succesfully\n";
	}

	/* get the type of file */
	char buffer[25];
	fgets(buffer, sizeof(buffer), fp);
	if(buffer[0]!='P' || buffer[1]!='6'){
		std::cout<<"[Error] File format not P6\n";
		exit(1);
	}
	else{
		std::cout<<"[OK] File format is P6\n";
	}

	/* now get different comments */
	buffer[0] = '#';
	int comments = 0;
	while(buffer[0]=='#'){
		fgets(buffer, sizeof(buffer),fp);
		comments++;
	}
	std::cout<<"[OK] Read "<<comments<<" comments succesfully\n";

	/* get the image size */
	width = height = 0;
	if(fscanf(fp, "%d %d", &width, &height)!=2){
		std::cout<<"[Error] File size could not be read\n";
		exit(1);
	}
	else{
		std::cout<<"[OK] File size " << width <<"x"<<height<<" px read succesfully\n";
	}

	/* get the component color */
	if (fscanf(fp, "%d", &nr_of_colors) != 1) {
		std::cout << "[Error] Reading nr of color components\n";
		exit(1);
	}
	else{
		std::cout << "[OK] Color components set at "<<nr_of_colors<<"\n";
	}

	/* checking for white spaces */
	int newline = 0;
	while (fgetc(fp) != '\n'){
		newline++;
	}
	std::cout<<"[OK] Counted "<<newline<<" newlines\n";

	/* now create the array */
	pixels = new PPMPixel[width*height];
	fread(pixels,1,COLOR_FORMAT*width*height, fp);
	std::cout<<"[OK] Loaded Image data\n";

	/* create the blob array */
	nr_blobs = 0;
	blobs = new int[width*height];
	for(int i = 0; i < width*height; i++){
		blobs[i] = 0;
	}
	std::cout<<"[OK] Initialized blob data\n";

	/* and init quads to nil */
	quads = NULL;
	std::cout<<"[OK] Init quads data to nil\n";
}

PPMImage::~PPMImage(){
	std::cout<<"\n[Img "<<img_id<<" Destructor] -------------------\n";
	width = height = nr_of_colors = 0;
	delete[] pixels;
	nr_blobs = 0;
	delete[] blobs;
	delete[] quads;

	std::cout<<"[OK] Deleted all image data\n";
}

void PPMImage::saveToFile(const char *filename){
	std::cout<<"\n[Img "<<img_id<<" Write to file] -------------------\n";
	/* open a file for writing */
	FILE *fp;
	if(!(fp = fopen(filename, "wb"))){
		std::cout << "[Error] Could not create file " << filename << " for writing!\n";
	}
	else{
		std::cout << "[OK] Created "<<filename<<" for writing\n";
	}

	/* Write the header first*/
	fprintf(fp, "P6\n");
	fprintf(fp, "# Created by Liviu\n");
	fprintf(fp, "%d %d\n",width,height);
	fprintf(fp, "%d\n",nr_of_colors);
	fwrite(pixels, COLOR_FORMAT * width, height, fp);
	fclose(fp);

	std::cout<<"[OK] Save image to file "<<filename<<"\n";
}

/* BW function */
void PPMImage::convertPPMToBW(int treshold){
	/* initial status message */
	std::cout<<"\n[Img "<<img_id<<" BW Filter] ------------\n";

	for (int row = 0; row < height; row++){
		for(int col = 0; col < width; col++){
			/* calculate current position */
			int pos = col+row*width;

			/* calculate the BW median */
			int new_red = (int)(pixels[pos].red*0.2126);
			int new_green = (int)(pixels[pos].green*0.7152);
			int new_blue = (int)(pixels[pos].blue*0.0722);
			unsigned char medie = new_red+new_green+new_blue;
			medie = (medie<treshold?0:255);

			/* set the new pixel value for the image */
			pixels[pos].red = medie;
			pixels[pos].green = medie;
			pixels[pos].blue = medie;

			/* also affect the blobs */
			blobs[pos] = 1 - (medie/255);
		}
	}

	/* final status message */
	std::cout<<"[OK] Image turned to BW\n";
}

/* set of functions used for blob detection */
void PPMImage::detectPPMBlobs(){
	/* initial status */
	std::cout<<"\n[Img "<<img_id<<"] Blob detector--------------------\n";

	/* init blob data */
	nr_blobs = 2;

	/* start recursive flood fill */
	for(int row = 0; row < height; row++){
		for(int col = 0; col < width; col+=BLOB_PASS){
			startFloodScan(col,row);
		}
	}

	/* status check */
	std::cout<<"[OK] Found out about "<<nr_blobs<<" blobs\n";
}

void PPMImage::startFloodScan(int col, int row){
	if(floodScan(col,row)){
		nr_blobs++;
	}
}

bool PPMImage::floodScan(int col, int row){
	int pos = col + row*width;

	if (col >= 0 && col < width &&
		row >= 0 && row < height &&
		pixels[pos].red == 0 && pixels[pos].red != 127 &&
	    blobs[pos] == 1)
	{
	        pixels[pos].red = 127;
	        blobs[pos] = nr_blobs;

	        floodScan(col-1, row);
	        floodScan(col+1, row);
	        floodScan(col, row-1);
	        floodScan(col, row+1);
	        return true;
	    }
	    else{
	        return false;
	    }
}

void PPMImage::processPPMQuads(){
	std::cout<<"\n[Img "<<img_id<<"] Quad processing--------------------\n";

	/* first init the quads array */
	quads = new PPMQuad[nr_blobs];

	for(int i = 2; i < nr_blobs; i++){
		/* minimum values used for line intersection */
		int min_x = INT_MAX, min_y = INT_MAX;
		int max_x = 0, max_y = 0;

		/* the array of points */
		for (int row = 0; row < height; row++) {
			for (int col = 0; col < width; col++) {
				int pos = col+row*width;
				if(blobs[pos]==i){
					/* check for mins and maximums */
					min_x = (col<min_x?col:min_x);
					max_x = (col>max_x?col:max_x);
					min_y = (row<min_y?row:min_y);
					max_y = (row>max_y?row:max_y);
				}
			}
		}

		quads[i].p1 = PPMPointMake(min_x, min_y);
		quads[i].p2 = PPMPointMake(max_x, min_y);
		quads[i].p3 = PPMPointMake(min_x, max_y);
		quads[i].p4 = PPMPointMake(max_x, max_y);
	}

	/* final status */
	std::cout<<"[OK] Processed all "<<nr_blobs<<" quads\n";
}

void PPMImage::savePPMQuadsToDisk(){
	std::cout<<"\n[Img "<<img_id<<" Write Quads to Disk] -------------------\n";

	for(int i = 2; i < nr_blobs; i++){
		/* create the filename */
		char filename[28];
		sprintf(filename,"resources/quads/img_%d.ppm",i);

		/* open a file for writing */
		FILE *fp;
		if(!(fp = fopen(filename, "wb"))){
			std::cout << "[Error] Could not create file " << filename << " for writing!\n";
		}

		/* prepare data */
		int qwidth = quads[i].p4.x - quads[i].p1.x;
		int qheight = quads[i].p4.y - quads[i].p1.y;
		PPMPixel *qpixels = new PPMPixel[qwidth*qheight];
		int qi = 0;
		for(int row = quads[i].p1.y; row < quads[i].p4.y; row++){
			for(int col = quads[i].p1.x; col < quads[i].p4.x; col++){
				int pos = col+row*width;
				qpixels[qi].red = pixels[pos].red;
				qpixels[qi].green = pixels[pos].green;
				qpixels[qi].blue = pixels[pos].blue;
				qi++;
			}
		}

		/* Write the header first*/
		fprintf(fp, "P6\n");
		fprintf(fp, "# Created by Liviu\n");
		fprintf(fp, "%d %d\n",qwidth,qheight);
		fprintf(fp, "%d\n",nr_of_colors);
		fwrite(qpixels, COLOR_FORMAT * qwidth, qheight, fp);
		fclose(fp);

		/* delete the pixels */
		delete[] qpixels;

		/* final stuff */
		std::cout<<"[OK] Quad "<<i-2<<" written to disk\n";
	}
}


