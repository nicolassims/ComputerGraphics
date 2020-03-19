#include "FileReader.h"
#include <stdio.h>
#include <string.h>
#include <map>
#include <cstdlib>

std::vector<std::string> tokenize(std::string s, std::string delimiter) {
	std::vector<std::string> tokens;
	size_t last = 0, next = 0;
	while ((next = s.find(delimiter, last)) != std::string::npos) {
		tokens.push_back(s.substr(last, next - last));
		last = next + 1;
	}
	tokens.push_back(s.substr(last, s.length() - 1));
	return tokens;
}

FileReader::FileReader(std::string filename) {
	this->formattedName = "";

	std::ifstream inFile(filename);
	if (inFile.is_open()) {
		std::string currentLine;
		while (std::getline(inFile, currentLine)) {
			std::vector<std::string> tokens = tokenize(currentLine, " ");
			if (!tokens[0].compare("v")) {
				parse(vertices, tokens);
			} else if (!tokens[0].compare("vn")) {
				parse(normals, tokens);
			} else if (!tokens[0].compare("vt")) {
				parse(textures, tokens);
			} else if (!tokens[0].compare("f")) {
				parseFace(tokens);
			} else if (!tokens[0].compare("mtllib")) {
				parseMtl(tokens, filename);
			}
		}
	}

	if (this->textures.size()) {
		this->combineIndexes();
	}
	inFile.close();
}

void FileReader::parse(std::vector<float> &pushee, std::vector<std::string> tokens) {//Passing by reference, otherwise vector isn't actually affected.
	for (int i = 1; i < tokens.size(); i++) {
		pushee.push_back(strtof(tokens[i].c_str(), 0));
	}
}

void FileReader::parseFace(std::vector<std::string> faces) {
	for (int i = 1; i < faces.size(); i++) {
		int firstDelimIndex = faces[i].find("/", 0);
		std::string vert = faces[i].substr(0, firstDelimIndex);
		std::string afterVert = faces[i].substr(firstDelimIndex + 1);
		int secondDelimIndex = afterVert.find("/", 0);
		std::string texture = afterVert.substr(0, secondDelimIndex);
		std::string norm = afterVert.substr(secondDelimIndex + 1);
		faceVertices.push_back(stoi(vert) - 1);
		faceTextures.push_back(stoi(texture) - 1);
		faceNormals.push_back(stoi(norm) - 1);
	}
}

std::string replaceFilename(std::string path, std::string filename) {
	std::string prefix = path.substr(0, path.rfind('/') + 1);
	return prefix + filename;
}

void FileReader::combineIndexes() {
	int indexNumber = 0;
	std::map<std::vector<float>, int> hashMap;
	for (int i = 0; i < this->faceVertices.size(); i++) {
		int vertexIndex = faceVertices[i];
		int textureIndex = faceTextures[i];

		std::vector<float> data;
		data.push_back(vertices[(vertexIndex * 3)]);
		data.push_back(vertices[(vertexIndex * 3) + 1]);
		data.push_back(vertices[(vertexIndex * 3) + 2]);
		data.push_back(textures[(textureIndex * 2)]);
		data.push_back(textures[(textureIndex * 2) + 1]);

		if (hashMap.count(data)) {
			combinedIndexes.push_back(hashMap[data]);
		} else {
			hashMap[data] = indexNumber;
			combinedPositionData.push_back(data[0]);
			combinedPositionData.push_back(data[1]);
			combinedPositionData.push_back(data[2]);
			combinedTextureData.push_back(data[3]);
			combinedTextureData.push_back(data[4]);
			combinedIndexes.push_back(indexNumber);
			indexNumber++;
		}
	}
}

void FileReader::parseMtl(std::vector<std::string> tokens, std::string filename) {
	std::string inFilename = replaceFilename(filename, tokens[1]);
	std::ifstream inFile(inFilename);
	if (inFile.is_open()) {
		std::string currentLine;
		while (std::getline(inFile, currentLine)) {
			std::vector<std::string> tok = tokenize(currentLine, " ");
			if (!tok[0].compare("map_Kd")) {
				this->formattedName = replaceFilename(filename, tok[1]);
			}
		}
	}
}