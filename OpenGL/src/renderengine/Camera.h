#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm/gtx/transform.hpp>

class Camera {

public:
	glm::vec3 position;
	float pitch, yaw, roll;

	static void createProjectionMatrix(glm::mat4 &out);
	Camera();
	~Camera();
	void move();
	void createViewMatrix(glm::mat4 &out) const;
};

