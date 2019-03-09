#include "Loader.h"
#include "../utils/mytypes.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

std::vector<uint> list_vaos;
std::vector<uint> list_vbos;
std::vector<uint> list_textures;

uint createVAO() {
	uint vaoid;
	glGenVertexArrays(1, &vaoid);
	list_vaos.push_back(vaoid);
	glBindVertexArray(vaoid);
	return vaoid;
}

void storeDataInAtrribList(uint attributeNum, int attribSize, const void *data, int dataSize) {
	uint vboid;
	glGenBuffers(1, &vboid);
	list_vbos.push_back(vboid);
	glBindBuffer(GL_ARRAY_BUFFER, vboid);
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	glVertexAttribPointer(attributeNum, attribSize, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}



void bindIndicesBuffer(const std::vector<int> &indices) {
	uint vboid;
	glGenBuffers(1, &vboid);
	list_vbos.push_back(vboid);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboid);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
}



namespace Loader {

	RawModel loadtoVAO(const std::vector<float> &positions, const std::vector<float> &textureCoords, const std::vector<float> &normals, const std::vector<int> &indices) {
		uint vaoid = createVAO();
		bindIndicesBuffer(indices);
		storeDataInAtrribList(0, 3, &positions[0], positions.size() * sizeof(float));
		storeDataInAtrribList(1, 2, &textureCoords[0], textureCoords.size() * sizeof(float));
		storeDataInAtrribList(2, 3, &normals[0], normals.size() * sizeof(float));
		unbindVAO();
		return RawModel(vaoid, indices.size());
	}

	uint loadTexture(const char *filename) {
		std::string filepath(filename);
		 
		uint texture;
		int width, height, numComponents;
		stbi_uc *imageData = stbi_load(("res/" + filepath + ".png").c_str(), &width, &height, &numComponents, 4);

		if (imageData == NULL) {
			fprintf(stderr, "ERROR: failed to load texture for '%s'\n", filename);
			exit(1);
		}
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		

		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_MAX_TEXTURE_LOD_BIAS, -0.4f);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
		list_textures.push_back(texture);
		stbi_image_free(imageData);
		return texture;
	}

	void cleanUp() {

		while (list_vaos.size() > 0) {
			glDeleteVertexArrays(1, &list_vaos.back());
			list_vaos.pop_back();
		}

		while (list_vbos.size() > 0) {
			glDeleteBuffers(1, &list_vbos.back());
			list_vbos.pop_back();
		}

		while (list_textures.size() > 0) {
			glDeleteTextures(1, &list_textures.back());
			list_textures.pop_back();

		}
	}

}
