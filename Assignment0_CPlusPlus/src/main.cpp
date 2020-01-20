// Include our custom library
//Compile by typing "g++ ppm.cpp main.cpp -o main"
#include "../include/PPM.h"

int main(){
    PPM myPPM("../textures/test1.ppm");
    myPPM.darken();
    myPPM.savePPM("../textures/test1_darken.ppm");

    return 0;
}