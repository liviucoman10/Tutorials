//============================================================================
// Name        : cpp_Lesson1.cpp
// Author      : Liviu Coman
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

/* include PPM Image header files */
#include "PPMImage.h"
#include "PPMAux.h"


int main() {
	std::cout << "Letter recognition program\n";

	PPMImage *my_img = new PPMImage("resources/test_img.ppm");
	writePPMToFile(my_img, "resources/test_img2.ppm");

	delete my_img;
	std::cout << "Reached end of program\n";

	return 0;
}
