/* Define the BMPAux class, that is initialized with a filename
 * and parses the BMP into an width x height pixel matrix
 */
#ifndef BMPAUX_H_
#define BMPAUX_H_

/* defines for the BMP Aux class */
#define BMP_COLOR_CMP 3
#define BMP_HEAD_SIZE 54
#define BMP_HEAD_WLOC 18
#define BMP_HEAD_HLOC 22

struct rgb_color{
	/* classical color components */
	unsigned int red;
	unsigned int green;
	unsigned int blue;

	/* the thresholded value (either 1 - white or 0 - black) */
	unsigned int t_val;
};

class BMPAux {
	/* internal static BMP id */
	static int		bmp_id;

	/* the width and the height of a BMP file */
	int				width;
	int				height;

	/* the pixels of a BMP file */
	rgb_color		*data;
public:

	/* public constructor and destructor */
	BMPAux(const char *filename);
	~BMPAux();

	/* public getters */
	int				getWidth();
	int				getHeight();
	rgb_color		getPixel(int col, int row);
};

#endif
