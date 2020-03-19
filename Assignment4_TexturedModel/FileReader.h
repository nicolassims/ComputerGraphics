#pragma once

#include <vector>
#include <fstream>
#include <sstream>

class FileReader {//Reads the obj file
public:
	FileReader(std::string filename);
	std::string formattedName;
	std::vector<float> vertices;
	std::vector<float> textures;
	std::vector<float> normals;

	std::vector<int> faceVertices;
	std::vector<int> faceTextures;
	std::vector<int> faceNormals;
	
	std::vector<float> combinedPositionData;
	std::vector<float> combinedTextureData;
	std::vector<int> combinedIndexes;
	
private:
	void parse(std::vector<float> &pushee, std::vector<std::string> tokens);
	void parseFace(std::vector<std::string> faces);
	void parseMtl(std::vector<std::string> mtls, std::string filename);
	void combineIndexes();
};
