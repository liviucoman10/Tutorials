/* PPM Image Aux file implementation */
#include "PPMAux.h"

/* include other useful IO functions */
#include <stdio.h>
#include <iostream>

void writePPMToFile(PPMImage *ref_img, const char *filename){
	/* open a file for writing */
	FILE *fp;
	if(!(fp = fopen(filename, "wb"))){
		std::cout << "Could not create file " << filename << " for writing!\n";
	}

	/* Write the header first*/
	fprintf(fp, "P6\n");
	fprintf(fp, "# Created by Liviu\n");
	fprintf(fp, "%d %d\n",ref_img->getWidth(),ref_img->getHeight());
	fprintf(fp, "%d\n",RGB_COMPONENT_COLOR);
	fwrite(ref_img->getPixels(), 3 * ref_img->getWidth(), ref_img->getHeight(), fp);

	fclose(fp);
}



