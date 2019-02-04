#include <GL/glew.h>
#include "Loader.h"
#include "../utils/mytypes.h"

std::vector<uint> vaos;
std::vector<uint> vbos;

uint createVAO() {
	uint vaoid;
	glGenVertexArrays(1, &vaoid);
	vaos.push_back(vaoid);
	glBindVertexArray(vaoid);
	return vaoid;
}

/*inline*/void unbindVAO() {
	glBindVertexArray(0);
}

void storeDataInAtrribList(uint attributeNum, void *data, int dataSize) {
	uint vboid;
	glGenBuffers(1, &vboid);
	vbos.push_back(vboid);
	glBindBuffer(GL_ARRAY_BUFFER, vboid);
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	glVertexAttribPointer(attributeNum, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}



void bindIndicesBuffer(std::vector<int> indices) {
	uint vboid;
	glGenBuffers(1, &vboid);
	vbos.push_back(vboid);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboid);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
}



namespace Loader {

	RawModel loadtoVAO(std::vector<float> positions, std::vector<int> indices) {
		uint vaoid = createVAO();
		bindIndicesBuffer(indices);
		storeDataInAtrribList(0, &positions[0], positions.size() * sizeof(float));
		unbindVAO();
		return RawModel(vaoid, indices.size());
	}

	void cleanUp() {

		while (vaos.size() > 0) {
			glDeleteVertexArrays(1, &vaos.back());
			vaos.pop_back();
		}

		while (vbos.size() > 0) {
			glDeleteBuffers(1, &vbos.back());
			vbos.pop_back();
		}
	}

}
