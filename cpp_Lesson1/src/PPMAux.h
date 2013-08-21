/* File that holds a number of auxiliary PPM functions */

#ifndef PPMAUX_H_
#define PPMAUX_H_

#include "PPMImage.h"

/* function that writes a ppm image to a file */
void writePPMToFile(PPMImage *ref_img, const char *filename);

#endif /* PPMAUX_H_ */
