// Includes for the assignment
#include "Vector4f.h"
#include "Matrix4f.h"
#include <iostream>

// Tests for comparing our library
// You may compare your operations against the glm library
// which is a well tested library.
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Sample unit test comparing against GLM.
bool unitTest0(){
	glm::mat4 glmIdentityMatrix = glm::mat4(1.0f);
	Matrix4f myIdentity( 1.0f,0,0,0,
        			     0,1.0f,0,0,
		        	     0,0,1.0f,0,
			             0,0,0,1.0f);
    if(glmIdentityMatrix[0][0]==myIdentity[0][0] &&
		glmIdentityMatrix[0][1]==myIdentity[0][1] &&
        glmIdentityMatrix[0][2]==myIdentity[0][2] &&
        glmIdentityMatrix[0][3]==myIdentity[0][3] &&
        glmIdentityMatrix[1][0]==myIdentity[1][0] &&
        glmIdentityMatrix[1][1]==myIdentity[1][1] &&
        glmIdentityMatrix[1][2]==myIdentity[1][2] &&
        glmIdentityMatrix[1][3]==myIdentity[1][3] &&
        glmIdentityMatrix[2][0]==myIdentity[2][0] &&
        glmIdentityMatrix[2][1]==myIdentity[2][1] &&
        glmIdentityMatrix[2][2]==myIdentity[2][2] &&
        glmIdentityMatrix[2][3]==myIdentity[2][3] &&
        glmIdentityMatrix[3][0]==myIdentity[3][0] &&
        glmIdentityMatrix[3][1]==myIdentity[3][1] &&
        glmIdentityMatrix[3][2]==myIdentity[3][2] &&
        glmIdentityMatrix[3][3]==myIdentity[3][3]){
			return true;
    }
    return false;
}

bool unitTest1(){
	glm::mat4 glmIdentityMatrix = glm::mat4(1.0f);
	Matrix4f myIdentity( 1.0f,0,0,0,
        			     0,1.0f,0,0,
		        	     0,0,1.0f,0,
			             0,0,0,1.0f);

    if(glmIdentityMatrix[0][0]==myIdentity(0,0) &&
        glmIdentityMatrix[0][1]==myIdentity(0,1) &&
        glmIdentityMatrix[0][2]==myIdentity(0,2) &&
        glmIdentityMatrix[0][3]==myIdentity(0,3) &&
        glmIdentityMatrix[1][0]==myIdentity(1,0) &&
        glmIdentityMatrix[1][1]==myIdentity(1,1) &&
        glmIdentityMatrix[1][2]==myIdentity(1,2) &&
        glmIdentityMatrix[1][3]==myIdentity(1,3) &&
        glmIdentityMatrix[2][0]==myIdentity(2,0) &&
        glmIdentityMatrix[2][1]==myIdentity(2,1) &&
        glmIdentityMatrix[2][2]==myIdentity(2,2) &&
        glmIdentityMatrix[2][3]==myIdentity(2,3) &&
        glmIdentityMatrix[3][0]==myIdentity(3,0) &&
        glmIdentityMatrix[3][1]==myIdentity(3,1) &&
        glmIdentityMatrix[3][2]==myIdentity(3,2) &&
        glmIdentityMatrix[3][3]==myIdentity(3,3)){
            return true;
    }
    return false;
}

// Sample unit test comparing against GLM.
bool unitTest2(){
	glm::mat4 glmIdentityMatrix = glm::mat4(1.0f);
	Vector4f a(1.0f ,0.0f,  0.0f,   0.0f);
	Vector4f b(0.0f ,1.0f,  0.0f,   0.0f);
	Vector4f c(0.0f ,0.0f,  1.0f,   0.0f);
	Vector4f d(0.0f ,0.0f,  0.0f,   1.0f);
	Matrix4f myIdentity(a,b,c,d);

    if(glmIdentityMatrix[0][0]==myIdentity[0][0] &&
        glmIdentityMatrix[0][1]==myIdentity[0][1] &&
        glmIdentityMatrix[0][2]==myIdentity[0][2] &&
        glmIdentityMatrix[0][3]==myIdentity[0][3] &&
        glmIdentityMatrix[1][0]==myIdentity[1][0] &&
        glmIdentityMatrix[1][1]==myIdentity[1][1] &&
        glmIdentityMatrix[1][2]==myIdentity[1][2] &&
        glmIdentityMatrix[1][3]==myIdentity[1][3] &&
        glmIdentityMatrix[2][0]==myIdentity[2][0] &&
        glmIdentityMatrix[2][1]==myIdentity[2][1] &&
        glmIdentityMatrix[2][2]==myIdentity[2][2] &&
        glmIdentityMatrix[2][3]==myIdentity[2][3] &&
        glmIdentityMatrix[3][0]==myIdentity[3][0] &&
        glmIdentityMatrix[3][1]==myIdentity[3][1] &&
        glmIdentityMatrix[3][2]==myIdentity[3][2] &&
        glmIdentityMatrix[3][3]==myIdentity[3][3]){
            return true;
    }
    return false;
}

// Sample unit test comparing against GLM.
bool unitTest3(){
	glm::mat4 glmScale = glm::mat4(2.0f);
	Vector4f a(1.0f,0,0,0);
	Vector4f b(0.0f,1.0f,0,0);
	Vector4f c(0,0,1.0f,0);
	Vector4f d(0,0,0,1.0f);
	Matrix4f myScaled(a,b,c,d);
    myScaled = myScaled.MakeScale(2.0f,2.0f,2.0f);

    if(
        glmScale[0][0]==myScaled[0][0] &&
        glmScale[0][1]==myScaled[0][1] &&
        glmScale[0][2]==myScaled[0][2] &&
        glmScale[0][3]==myScaled[0][3] &&
        glmScale[1][0]==myScaled[1][0] &&
        glmScale[1][1]==myScaled[1][1] &&
        glmScale[1][2]==myScaled[1][2] &&
        glmScale[1][3]==myScaled[1][3] &&
        glmScale[2][0]==myScaled[2][0] &&
        glmScale[2][1]==myScaled[2][1] &&
        glmScale[2][2]==myScaled[2][2] &&
        glmScale[2][3]==myScaled[2][3] &&
        glmScale[3][0]==myScaled[3][0] &&
        glmScale[3][1]==myScaled[3][1] &&
        glmScale[3][2]==myScaled[3][2] &&
        glmScale[3][3]!=myScaled[3][3]){
            return true;
    }

    return false;
}

// Sample unit test comparing against GLM.
// Testing operator
bool unitTest4(){
	glm::mat4 glmTest = glm::mat4(1.0f);
    glmTest[1][3] = 72.0f;
    glmTest[2][3] = 2.1f;

	Matrix4f myMatrix(0,0,0,0,
                      0,0,0,0,
                      0,0,0,0,
                      0,0,0,0);

    myMatrix[1][3] = 72.0f;
    myMatrix[2][3] = 2.1f;

    if( glmTest[1][3]==myMatrix[1][3] &&
        glmTest[2][3]==myMatrix[2][3] ){
            return true;
    }

    return false;
}

// Sample unit test testing your library
bool unitTest5(){
	Vector4f a(1,1,1,1);
	Vector4f b(0,0,0,0);
	Vector4f c = a + b;

	if(c.x == 1 && c.y == 1 && c.z ==1 && c.w==1){
		return true;
	}
	return false;
}

bool unitTest6() {
	Vector4f v = Vector4f(1, 2, 3, 4);

	v *= 4;
	if (!(v.x == 4 && v.y == 8 && v.z == 12 && v.w == 16)) { return false; }

	v *= -0.5;
	if (!(v.x == -2 && v.y == -4 && v.z == -6 && v.w == -8)) { return false; }

	v *= 0;
	if (!(v.x == 0 && v.y == 0 && v.z == 0 && v.w == 0)) { return false; }

	return true;
}

bool unitTest7() {
	Vector4f v = Vector4f(1, 2, 4, 8);

	v /= 2;
	if (!(v.x == 0.5f && v.y == 1 && v.z == 2 && v.w == 4)) { return false; }

	v /= -0.5;
	if (!(v.x == -1 && v.y == -2 && v.z == -4 && v.w == -8)) { return false; }

	try {
		v /= 0;
	} catch (std::invalid_argument e) {
		return true;
	}
	return false;
}

bool unitTest8() {
	Vector4f v = Vector4f(1, 2, 4, 8);

	v += v;
	if (!(v.x == 2 && v.y == 4 && v.z == 8 && v.w == 16)) { return false; }

	v += v * -2;
	if (!(v.x == -2 && v.y == -4 && v.z == -8 && v.w == -16)) { return false; }

	v += Vector4f(0, 0, 0, 0);
	if (!(v.x == -2 && v.y == -4 && v.z == -8 && v.w == -16)) { return false; }

	return true;
}

bool unitTest9() {
	Vector4f v = Vector4f(1, 2, 4, 8);

	v -= v * 0.5;
	if (!(v.x == 0.5f && v.y == 1 && v.z == 2 && v.w == 4)) { return false; }

	v -= -v;
	if (!(v.x == 1 && v.y == 2 && v.z == 4 && v.w == 8)) { return false; }

	v -= Vector4f(0, 0, 0, 0);
	if (!(v.x == 1 && v.y == 2 && v.z == 4 && v.w == 8)) { return false; }

	return true;
}

bool unitTest10() {
	Vector4f v = Vector4f(1, 2, 4, 8);
	return Dot(v, v) == 85;
}

bool unitTest11() {
	return Magnitude(Project(Vector4f(1, 3, 5, 7), Vector4f(1, 2, 4, 8))) == Magnitude(Vector4f(83.0f/84, 83.0f/28, 415.0f/84, 83.0f/12));
}

bool unitTest12() {
	Vector4f v = Vector4f(1, 2, 4, 8);
	return Magnitude(v) != 1 && Magnitude(Normalize(v)) == 1;
}

bool unitTest13() {
	return Magnitude(CrossProduct(Vector4f(1, 3, 5, 1), Vector4f(2, 4, 8, 1))) == Magnitude(Vector4f(4, 2, -2, 1));
}

bool unitTest14() {
	Matrix4f m = Matrix4f(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	Matrix4f mm = m * m;

	return mm[0][0] == 90 && mm[0][1] == 100 && mm[0][2] == 110 && mm[0][3] == 120 &&
		mm[1][0] == 202 && mm[1][1] == 228 && mm[1][2] == 254 && mm[1][3] == 280 &&
		mm[2][0] == 314 && mm[2][1] == 356 && mm[2][2] == 398 && mm[2][3] == 440 &&
		mm[3][0] == 426 && mm[3][1] == 484 && mm[3][2] == 542 && mm[3][3] == 600;
}

bool unitTest15() {
	Matrix4f m = Matrix4f(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	Vector4f mv = m * Vector4f(1, 2, 4, 8);
	return mv[0] == 49 && mv[1] == 109 && mv[2] == 169 && mv[3] == 229;
}

int main(){
    // Keep track of the tests passed
    unsigned int testsPassed = 0;

    // Run 'unit tests'
    std::cout << "Passed 0: " << unitTest0() << " \n";
    std::cout << "Passed 1: " << unitTest1() << " \n";
    std::cout << "Passed 2: " << unitTest2() << " \n";
    std::cout << "Passed 3: " << unitTest3() << " \n";
    std::cout << "Passed 4: " << unitTest4() << " \n";
    std::cout << "Passed 5: " << unitTest5() << " \n";
	std::cout << "Passed 6: " << unitTest6() << " \n";
	std::cout << "Passed 7: " << unitTest7() << " \n";
	std::cout << "Passed 8: " << unitTest8() << " \n";
	std::cout << "Passed 9: " << unitTest9() << " \n";
	std::cout << "Passed 10: " << unitTest10() << " \n";
	std::cout << "Passed 11: " << unitTest11() << " \n";
	std::cout << "Passed 12: " << unitTest12() << " \n";
	std::cout << "Passed 13: " << unitTest13() << " \n";
	std::cout << "Passed 14: " << unitTest14() << " \n";
	std::cout << "Passed 15: " << unitTest15() << " \n";

    return 0;
}
