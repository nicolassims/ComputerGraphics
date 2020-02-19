#include "FileReader.h"

FileReader::FileReader(std::string path) {
	std::ifstream file(path);
	if (!file) {
		std::cerr << "File path not found." << std::endl;
		exit(1);
	}
	std::string line;
	while (std::getline(file, line)) {//line = "v -1.00000000 -1.00000000 -1.00000000"
		std::vector<std::string> inputVector = FileReader::split(line, "\\s+");//inputVector = ["v", "-1.00000000", "-1.00000000", "-1.00000000"]

		if (line.substr(0, 2) == "v " || line.substr(0, 3) == "vn ") {
			Vector3 input;
			input.x = std::stof(inputVector[1]);//input.x = -1.00000000f
			input.y = std::stof(inputVector[2]);//input.y = -1.00000000f
			input.z = std::stof(inputVector[3]);//input.z = -1.00000000f
			if (line.substr(0, 2) == "v ") {
				vertices.push_back(input);//vertices[vertices.size() - 1] = Vector3(-1.00000000f, -1.00000000f, -1.00000000f)
			} else {
				normals.push_back(input);
			}
		} else if (line.substr(0, 2) == "f ") {//line = f 1//1 5//5 2//2
			for (int i = 1; i < inputVector.size(); i++) {
				std::vector<std::string> grabbedVertices = FileReader::split(inputVector[i], "\/\/");//grabbedVertices = [1, 1]
				indices.push_back(std::stoi(grabbedVertices[0]));//indices[indices.size() - 1] = 1
			}
		}
	}
	file.close();
}

//Splits a provided string into a vector of strings that match a provided regex token.
std::vector<std::string> FileReader::split(std::string matchee, std::string token) {//Just use built-in regex for this, easier than figuring it out from scratch
	std::regex regex(token);
	std::vector<std::string> out(std::sregex_token_iterator(matchee.begin(), matchee.end(), regex, -1), std::sregex_token_iterator());
	return out;
}

// Retrieves the vertices
std::vector<float> FileReader::getVertices() {
	std::vector<float> verts;
	for (int i = 0; i < vertices.size(); i++) {
		verts.push_back(vertices[i].x);
		verts.push_back(vertices[i].y);
		verts.push_back(vertices[i].z);
	}
	return verts;
}

// Retrieves the normals
std::vector<float> FileReader::getNormals() {
	std::vector<float> norms;
	for (int i = 0; i < normals.size(); i++) {
		norms.push_back(normals[i].x);
		norms.push_back(normals[i].y);
		norms.push_back(normals[i].z);
	}
	return norms;
}

// Returns the indices, off by one
std::vector<unsigned int> FileReader::getIndices() {
	std::vector<unsigned int> returnable;
	for (int i = 0; i < indices.size(); i++) {
		returnable.push_back(indices[i] - 1);
	}
	return returnable;
}

//returns the index pairs that make up the lines of the model
std::vector<unsigned int> FileReader::getLines() {
	std::vector<unsigned int> returnable;
	for (int i = 0; i < indices.size(); i += 3) {
		returnable.push_back(indices[i] - 1);//First index to...
		returnable.push_back(indices[i + 1] - 1);//second.
		returnable.push_back(indices[i + 1] - 1);//Second index to...
		returnable.push_back(indices[i + 2] - 1);//third.
		returnable.push_back(indices[i + 2] - 1);//third index to...
		returnable.push_back(indices[i] - 1);//first
	}
	return returnable;
}
