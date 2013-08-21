//============================================================================
// Name        : cpp_Lesson1.cpp
// Author      : Liviu Coman
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "BMPAux.h"
#include "ImageAux.h"

using namespace std;

int main() {
	cout << "Letter recognition program" << endl;

	/* create an unsigned char array to read image data */
	BMPAux img_1("resources/test_img.bmp");
	thresholdBMP(img_1, 200);

	return 0;
}
