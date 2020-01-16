/** @file main.cpp
 *  @brief Entry point into our program.
 *  
 *  Welcome to the Great Looking Software Render 
 *  code base (Yes, I needed something with a gl prefix).
 *
 *  This is where you will implement your graphics API.
 *
 *  Compile on the terminal with: 
 *
 *  clang++ -std=c++11 main.cpp -o main
 *
 *  @author Mike Shah
 *  @bug No known bugs.
 */

// Load our libraries
#include <iostream>

// Some define values
#define WINDOW_HEIGHT 320
#define WINDOW_WIDTH 320

// C++ Standard Libraries
#include <iostream>
#include <algorithm>

// User libraries
#include "GL.h"
#include "Color.h"
#include "TGA.h"
#include "Maths.h"

// Create a canvas to draw on.
TGA canvas(WINDOW_WIDTH,WINDOW_HEIGHT);

// Implementation of Bresenham's Line Algorithm
// The input to this algorithm is two points and a color
// This algorithm will then modify a canvas (i.e. image)
// filling in the appropriate colors.
void drawLine(Vec2 v0, Vec2 v1, TGA& image, ColorRGB c){
    bool steep = false;
    if(std::abs(v0.x-v1.x)<std::abs(v0.y-v1.y)){
        // If the line is steep we want to transpose the image.
        std::swap(v0.x,v0.y);
        std::swap(v1.x,v1.y);
        steep = true;
    }
    if(v0.x>v1.x){  // make it left-to-right
        std::swap(v0.x, v1.x);
        std::swap(v0.y, v1.y);
    }
    for(int x = v0.x; x <= v1.x; ++x){
        float t = (x-v0.x)/(float)(v1.x-v0.x);
        int y = v0.y*(1.0f-t) + v1.y*t;
        if(steep){
            canvas.setPixelColor(y,x,c);
        }else{
            canvas.setPixelColor(x,y,c);
        }
    }
}

float sign(Vec2 p1, Vec2 p2, Vec2 p3) {
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool PointInTriangle(Vec2 pt, Vec2 v1, Vec2 v2, Vec2 v3) {
	float d1 = sign(pt, v1, v2), d2 = sign(pt, v2, v3), d3 = sign(pt, v3, v1);
	bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0), has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);
	float d1, d2, d3;
	bool has_neg, has_pos;

	d1 = sign(pt, v1, v2);
	d2 = sign(pt, v2, v3);
	d3 = sign(pt, v3, v1);

	has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(has_neg && has_pos);
}

// Draw a triangle
void triangle(Vec2 v0, Vec2 v1, Vec2 v2, TGA &image, ColorRGB c){
    if (glFillMode==LINE){
        drawLine(v0,v1,image,c);
        drawLine(v1,v2,image,c);
        drawLine(v2,v0,image,c);
	} else if (glFillMode == FILL) {
		int minx = std::min(v0.x, std::min(v1.x, v2.x));
		int maxx = std::max(v0.x, std::max(v1.x, v2.x));
		int miny = std::min(v0.y, std::min(v1.y, v2.y));
		int maxy = std::max(v0.y, std::max(v1.y, v2.y));
		int counter = 0;
		for (int i = minx; i < maxx; i++) {
			bool columnstarted = false;
			for (int j = miny; j < maxy; j++) {
				counter++;
				if (PointInTriangle(Vec2(i,j), v0, v1, v2)) {
					columnstarted = true;
					canvas.setPixelColor(i, j, c);
				} else if (columnstarted) {
					break;
				}
			}
		}
	}

		//FIX THIS
		std::cout << v0.x << "," << v0.y << "," << v1.x << "," << v1.y << "," << v2.x << "," << v2.y << std::endl;

		//if (v1.y < v0.y) { swap(v1, v0); }
		//if (v2.y < v0.y) { swap(v2, v0); }
		//if (v2.y < v1.y) { swap(v2, v1); }

		//FIX THIS
		std::cout << v0.x << "," << v0.y << "," << v1.x << "," << v1.y << "," << v2.x << "," << v2.y << std::endl;

		int counter = 0;
		for (int i = minx; i < maxx; i++) {
			bool columnstarted = false;
			for (int j = miny; j < maxy; j++) {
				counter++;
				if (PointInTriangle(Vec2(i,j), v0, v1, v2)) {
					columnstarted = true;
					canvas.setPixelColor(i, j, c);
				} else if (columnstarted) {
					break;
				}
			}
		}
	}
}

// Main
int main(){
    // A sample of color(s) to play with
    ColorRGB red, blue, green;
    red.r = 255; red.g = 0; red.b = 0;
	blue.r = 0; blue.g = 0; blue.b = 255;
	green.r = 0; green.g = 255; green.b = 0;

	// Points for our Line
	Vec2 line[2] = { Vec2(0,0), Vec2(100,100) };

	// Set the fill mode
	glPolygonMode(FILL);

	// Draw a line
	drawLine(line[0], line[1], canvas, red);

	// Data for our triangle
	Vec2 tri[3] = { Vec2(0,320), Vec2(320,320), Vec2(160,0) };
	Vec2 tri1[3] = { Vec2(160,320), Vec2(0,160), Vec2(320,160) };
	Vec2 tri2[3] = { Vec2(11,213), Vec2(213,312), Vec2(312,11) };

	glFillMode = FILL;

	// Draw a triangle
	triangle(tri[0], tri[1], tri[2], canvas, red);
	triangle(tri2[0], tri2[1], tri2[2], canvas, green);
	triangle(tri1[0], tri1[1], tri1[2], canvas, blue);

	// Points for our Line
	Vec2 line[2] = { Vec2(0,0), Vec2(100,100) };

	// Set the fill mode
	glPolygonMode(FILL);

	// Draw a line
	drawLine(line[0], line[1], canvas, red);

	// Data for our triangle
	Vec2 tri[3] = { Vec2(0,320), Vec2(320,320), Vec2(160,0) };
	Vec2 tri1[3] = { Vec2(160,320), Vec2(0,160), Vec2(320,160) };
	Vec2 tri2[3] = { Vec2(11,213), Vec2(213,312), Vec2(312,11) };

	glFillMode = FILL;

	// Draw a triangle
	triangle(tri[0], tri[1], tri[2], canvas, red);
	triangle(tri2[0], tri2[1], tri2[2], canvas, green);
	triangle(tri1[0], tri1[1], tri1[2], canvas, blue);

		// Output the final image
	canvas.outputTGAImage("graphics_lab2.ppm");

    return 0;
}