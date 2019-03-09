#include "objparser.h"

#include "../Loader.h"

#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <array>
#include <ctime>


void processVertices(const char *line, std::vector<int> &indices, const std::vector<float> &textures, const std::vector<float> &normals,
	std::vector<float> &newtextures, std::vector<float> &newnormals) {

	int vertexData[9];
	sscanf_s(line, "%d/%d/%d %d/%d/%d %d/%d/%d", &vertexData[0], &vertexData[1], &vertexData[2], &vertexData[3], &vertexData[4],
		&vertexData[5], &vertexData[6], &vertexData[7], &vertexData[8]);

	for (int i = 0; i <= 6; i += 3) {
		int vertexptr = vertexData[i + 0] - 1;
		indices.push_back(vertexptr);

		int currentTexture = (vertexData[i + 1] - 1) * 2;
		newtextures[vertexptr * 2] = textures[currentTexture];
		newtextures[vertexptr * 2 + 1] = 1 - textures[currentTexture + 1];

		int currentNormal = (vertexData[i + 2] - 1) * 3;
		newnormals[vertexptr * 3] = normals[currentNormal];
		newnormals[vertexptr * 3 + 1] = normals[currentNormal + 1];
		newnormals[vertexptr * 3 + 2] = normals[currentNormal + 2];

	}
}

RawModel objparser::loadObjModel(const char *fileName) {
	
	std::string name("res/");
	name += fileName;
	name += ".obj";

	const char *filePath = name.c_str();

	std::ifstream fin;
	fin.open(filePath);

	if (fin.fail()) {
		fprintf(stderr, "unable to open OBJ file '%s'\n", filePath);
		exit(1);
	}

	std::string lnbuf;
	const char *line;
	std::vector<float> vertices;
	std::vector<float> pre_textures;
	std::vector<float> pre_normals;
	std::vector<int> indices;

	std::vector<float> textures, normals;
	bool initvecs = true;

	std::string type;

	clock_t start = clock();

	while (std::getline(fin, lnbuf)) {
		type = lnbuf.substr(0, 2);
		lnbuf = lnbuf.substr(2);
		line = lnbuf.c_str();
		if (type == "v ") {
			float x, y, z;
			sscanf_s(line, "%f %f %f", &x, &y, &z);
			vertices.push_back(x); vertices.push_back(y); vertices.push_back(z);
		}
		else if (type == "vt") {
			float x, y;
			sscanf_s(line, "%f %f", &x, &y);
			pre_textures.push_back(x); pre_textures.push_back(y);
		}
		else if (type == "vn") {
			float x, y, z;
			sscanf_s(line, "%f %f %f", &x, &y, &z);
			pre_normals.push_back(x); pre_normals.push_back(y); pre_normals.push_back(z);
		}
		else if (type == "f ") {
			if (initvecs) {
				textures.resize(vertices.size() / 3 * 2);
				normals.resize(vertices.size());
				initvecs = false;
			}
			processVertices(line, indices, pre_textures, pre_normals, textures, normals);
		}
		
	}

	clock_t end = clock();

	fin.close();

	printf("OBJParser:  loading time for model '%s': %f seconds \n", fileName, double(end - start) / CLOCKS_PER_SEC);

	return Loader::loadtoVAO(vertices, textures, normals, indices);
}

