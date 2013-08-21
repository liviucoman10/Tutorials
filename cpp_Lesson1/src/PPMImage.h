/* Implementation of the PPM image format as a class */

#ifndef PPMIMAGE_H_
#define PPMIMAGE_H_

#define PPM_COLOR_FORMAT	3
#define RGB_COMPONENT_COLOR 255

/* Structure that holds a RGB Color - reg, green, blue */
typedef struct {
	unsigned char 	red, green, blue;
} PPMPixel;

/* the actual class that holds the image */
class PPMImage{
	int				width, height;
	PPMPixel		*pixels;

public:
	/* constructor and destructor */
	PPMImage(const char *source);
	~PPMImage();

	/* public getters, setters */
	PPMPixel		getPixel(int col, int row);
	PPMPixel		*getPixels();
	int				getWidth();
	int				getHeight();
};

#endif
