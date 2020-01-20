#include "../include/PPM.h"
#include <fstream>
#include <string> // new library!
#include <vector>
#include <algorithm>

// Constructor loads a filename with the .ppm extension
PPM::PPM(std::string fileName) {
	// Opens a file to output
	std::ifstream inFile;

	// Now we can open our file.
	inFile.open(fileName);

	// Lets also check to make sure the filepath is correct.
	if (inFile.is_open()) {
		//There are three consistent header lines in each file, not counting comments.
		//Version Number, width/height, and max value
		int headerLines = 3;

		//The max value for a PPM should be 255.
		float maxValue = 255.0;

		//The line being read.
		std::string line;

		//The array of rgb colors
		std::vector<unsigned char> coordinates;

		//Iterate through the file, reading it line by line.
		while (getline(inFile, line)) {
			//Ignore comments
			if (line.substr(0, 1) != "#") {

				//Once all the header lines are dealt with, you can start reading the actual values from the PPM
				if (headerLines == 0) {
					coordinates.push_back((unsigned char)std::stoi(line));
				} else {
					headerLines--;

					//Handle the width/height
					if (headerLines == 1) {
						int space = line.find(" ");
						m_width = std::stoi(line.substr(0, space));
						m_height = std::stoi(line.substr(space, line.length()));

					//Handle whatever value the PPM is currently scaled to
					} else if (headerLines == 0) {
						maxValue = std::stod(line);
					}
				}
			}
		}
		
		//Assign an array to the private variable pointer
		m_PixelData = new unsigned char[m_width * m_height * 3];

		//Scale the values, if necessary
		for (int i = 0; i < coordinates.size(); i++) {
			m_PixelData[i] = coordinates.at(i) * 255.0 / maxValue;
		}

		//Free up the Vector's memory
		coordinates.erase(coordinates.begin(), coordinates.end());
	}
	//Close the file we're reading from
	inFile.close();
}

// Destructor clears any memory that has been allocated
PPM::~PPM() {
	delete[] m_PixelData;
}

// Saves a PPM Image to a new file.
void PPM::savePPM(std::string outputFileName) {
	//Open the file to write to
	std::ofstream outFile(outputFileName);

	//Make sure the file is correctly opened
	if (outFile.is_open()) {

		//Stream out the header
		outFile << "P3\n# CREATOR: Nicolas Karayakaylar\n" << m_width << " " << m_height << "\n255" << std::endl;

		//Stream out the PPM's data
		for (int i = 0; i < m_width * m_height * 3; i++) {
			outFile << (int)m_PixelData[i] << std::endl;
		}
	}

	//Close the file being streamed to
	outFile.close();
}

// Darken subtracts 50 from each of the red, green and blue color components of all of the pixels in the PPM. Note that no values may be less than 0 in a ppm.
void PPM::darken() {
	for (int i = 0; i < m_width * m_height * 3; i++) {
		//Decrease the value of a cell's RGB values by 50, or set it to zero, if it's already below 50.
		m_PixelData[i] = std::max(m_PixelData[i] - 50, 0);
	}
}

// Sets a pixel to a specific R,G,B value 
void PPM::setPixel(int x, int y, int R, int G, int B) {
	int slot = x * 3 + y * m_width * 3;
	m_PixelData[slot] = R;
	m_PixelData[slot + 1] = G;
	m_PixelData[slot + 2] = B;
}