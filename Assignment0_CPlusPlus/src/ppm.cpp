#include "../include/PPM.h"
#include <fstream>
#include <string> // new library!
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>//FIX THIS


// Constructor loads a filename with the .ppm extension
PPM::PPM(std::string fileName) {
	// Opens a file to output
	// You will notice the name is 'ifstream'
	// This means 'input file stream'
	std::ifstream inFile;

	// Now we are going to read in some data.
	// I want to actually make our program more flexible
	// and read in a file from the command line.
	// To do this, we'll use the argc, and argv**
	// arguments of our main function.
	// So when we run our program, we will type on the command-line:
	// ./input objects/bunny.obj"

	// Now we can open our file.
	// Think about why this is argv[1].
	// Try printing it out to see what this is.
	inFile.open(fileName);

	// Lets also check to make sure the filepath is correct.
	if (inFile.is_open()) {
		// Now we can do some work
		// We'll learn about strings in a moment,
		// but we are using getline to read in
		// one string of text at a time, until
		// we have nothing left to read.
		int headerLines = 3;
		float maxValue = 255.0;
		std::string line;   // A string object.
		std::vector<unsigned char> coordinates;
		while (getline(inFile, line)) {
			if (line.substr(0, 1) != "#") {
				if (headerLines == 0) {
					coordinates.push_back((unsigned char)std::stoi(line));
				} else {
					headerLines--;
					if (headerLines == 1) {
						int space = line.find(" ");
						m_width = std::stoi(line.substr(0, space));
						m_height = std::stoi(line.substr(space, line.length()));
					} else if (headerLines == 0) {
						maxValue = std::stod(line);
					}
				}
			}
		}

		m_PixelData = new unsigned char[m_width * m_height * 3];
		for (int i = 0; i < coordinates.size(); i++) {
			m_PixelData[i] = coordinates.at(i) * 255.0 / maxValue;
		}
		coordinates.erase(coordinates.begin(), coordinates.end());
	}
	inFile.close();
}

// Destructor clears any memory that has been allocated
PPM::~PPM() {
	delete[] m_PixelData;
}

// Saves a PPM Image to a new file.
void PPM::savePPM(std::string outputFileName) {
	std::ofstream outFile(outputFileName);
	if (outFile.is_open()) {
		outFile << "P3\n# CREATOR: Nicolas Karayakaylar\n" << m_width << " " << m_height << "\n255" << std::endl;
		for (int i = 0; i < m_width * m_height * 3; i++) {
			outFile << (int)m_PixelData[i] << std::endl;
		}
	}
	outFile.close();
}

// Darken subtracts 50 from each of the red, green
// and blue color components of all of the pixels
// in the PPM. Note that no values may be less than
// 0 in a ppm.
void PPM::darken() {
	for (int i = 0; i < m_width * m_height * 3; i++) {
		unsigned char darkDarkerYetDarker = std::max(m_PixelData[i] - 50, 0);
		m_PixelData[i] = darkDarkerYetDarker;
	}
}

// Sets a pixel to a specific R,G,B value 
void PPM::setPixel(int x, int y, int R, int G, int B) {
	int slot = x * 3 + y * m_width * 3;
	m_PixelData[slot] = R;
	m_PixelData[slot + 1] = G;
	m_PixelData[slot + 2] = B;
}