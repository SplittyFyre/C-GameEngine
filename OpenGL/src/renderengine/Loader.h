#pragma once

#include <GL/glew.h>
#include <vector>
#include "models.h"

namespace Loader {
	RawModel loadtoVAO(const std::vector<float> &positions, const std::vector<float> &textureCoords, const std::vector<float> &normals, const std::vector<int> &indices);
	void cleanUp();
	uint loadTexture(const char *filename);

	inline void unbindVAO() { glBindVertexArray(0); }
}