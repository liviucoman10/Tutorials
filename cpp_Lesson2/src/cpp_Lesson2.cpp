#include <iostream>
#include "PPMImage.h"

using namespace std;

int main() {
	std::cout << "Program start\n";

	PPMImage *my_img = new PPMImage("resources/test_img.ppm");
	my_img->convertPPMToBW(230);
	my_img->detectPPMBlobs();
	my_img->processPPMQuads();
	my_img->savePPMQuadsToDisk();
	my_img->saveToFile("resources/test_img2.ppm");
	delete my_img;

	std::cout << "Program ends\n";
	return 0;
}
