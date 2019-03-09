#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm/gtx/transform.hpp>

namespace sfmath {
	void createTransformationMatrix(glm::mat4 &dest, const glm::vec3 &translation, const glm::vec3 &rotation, const glm::vec3 &scale);
}