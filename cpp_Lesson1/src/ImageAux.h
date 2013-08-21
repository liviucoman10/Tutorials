/* Header file that defines a bunch of img. aux functions */

#ifndef IMAGEAUX_H_
#define IMAGEAUX_H_

#include "BMPAux.h"

/* function that takes a reference to a BMPAux object and a treshold value
 * it then proceeds to make the BMPAux object black&white and tresholded
 */
void thresholdBMP(BMPAux &ref_bmpaux, int treshold);


#endif /* IMAGEAUX_H_ */
