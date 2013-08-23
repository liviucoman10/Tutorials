/* here is where I define a few basic data structures */

#ifndef PPMAUX_H_
#define PPMAUX_H_

typedef struct {
	unsigned char red, green, blue;
}PPMPixel;

typedef struct{
	int	x, y;
}PPMPoint;

typedef struct{
	PPMPoint p1, p2, p3, p4;
}PPMQuad;

static inline PPMPoint PPMPointMake(int x, int y){
	PPMPoint new_pct;
	new_pct.x = x;
	new_pct.y = y;
	return new_pct;
}

#endif
