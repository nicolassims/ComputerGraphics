#ifndef FILEREADER
#define FILEREADER

#include <string>
#include <vector>

class FileReader {
public:
	FileReader(std::string path);

	struct Vector3 {
		float x, y, z;
	};

	//Returns a vector of vertices, clumped up in threes
	std::vector<Vector3> getVertices();

	//Returns a vector of normals, clumped up in threes
	std::vector<Vector3> getNormals();

	//returns a vector of the indices of the object
	std::vector<unsigned int> getIndices();

	//returns a vector of the lines of the object
	std::vector<unsigned int> getLines();

private:
	std::vector<Vector3> vertices;
	std::vector<Vector3> normals;
	std::vector<unsigned int> indices;

	//returns a vector of the strings that match the provided regex token
	std::vector<std::string> split(std::string matchee, std::string token);
};

#endif