/* Definition of PPM Image */
#ifndef PPMIMAGE_H_
#define PPMIMAGE_H_

#import "PPMAux.h"

#define COLOR_FORMAT 	3
#define BLOB_PASS 		5

class PPMImage{
	/* image ID vars */
	static int	simg_id;
	int			img_id;

	/* img data vars */
	int			width, height;
	int			nr_of_colors;
	PPMPixel	*pixels;

	/* blob data */
	int			nr_blobs;
	int			*blobs;

	/* declare the quads */
	PPMQuad		*quads;
public:
	PPMImage(const char *filename);
	~PPMImage();

	/* save to file function */
	void		saveToFile(const char *filename);

	/* BW function */
	void 		convertPPMToBW(int treshold);

	/* set of functions used for blob detection */
	void 		detectPPMBlobs();
	void 		startFloodScan(int col, int row);
	bool 		floodScan(int col, int row);
	void		processPPMQuads();
	void		savePPMQuadsToDisk();
};

#endif
