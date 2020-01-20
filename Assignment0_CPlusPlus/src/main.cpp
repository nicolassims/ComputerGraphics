// Include our custom library

//Compile by typing "g++ ppm.cpp main.cpp -o main"
#include "../include/PPM.h"

int main(){

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