#include "sfmath.h"

namespace sfmath {
	void createTransformationMatrix(glm::mat4 &dest, const glm::vec3 &translation, const glm::vec3 &rotation, const glm::vec3 &scale) {
		
		glm::mat4 rotMatrix =
			glm::rotate(glm::radians(rotation.y), glm::vec3(0, 1, 0)) *
			glm::rotate(glm::radians(rotation.x), glm::vec3(1, 0, 0)) *
			glm::rotate(glm::radians(rotation.z), glm::vec3(0, 0, 1));

		glm::mat4 scaleMatrix = glm::scale(scale);

		dest = glm::translate(translation) * rotMatrix * scaleMatrix;
	}
}