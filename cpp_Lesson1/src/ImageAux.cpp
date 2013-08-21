/* ImageAux implementation */
#include "ImageAux.h"

#include <iostream>

void thresholdBMP(BMPAux &ref_bmpaux, int treshold){
	/* go through all the pixels */
	for(int row = 0; row < ref_bmpaux.getHeight(); row++){
		for(int col = 0; col < ref_bmpaux.getWidth(); col++){
			/* calculate the black and white value of the pixel */
			int bw_medie = ref_bmpaux.getPixel(col, row)*0.2126 + ref_bmpaux.getPixel(col, row)*0.7152 +  ref_bmpaux.getPixel(col, row)*0.0722;
			/* if the BW value is below the threshold, put the t_val as 1 (white),
			 * else, put it as 0 (black)
			 */
			ref_bmpaux.getPixel(col, row).t_val = (bw_medie<treshold?0:1);
		}
	}
}

