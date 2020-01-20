// Include our custom library
#include "../include/PPM.h"
#include <iostream>//FIX THIS

int main(){

    PPM myPPM("../textures/test1.ppm");
    myPPM.darken();
    myPPM.savePPM("../textures/test1_darken.ppm");

	int dummy;
	std::cin >> dummy;
    return 0;
}
