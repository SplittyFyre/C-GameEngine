#include "Camera.h"

#include "DisplayManager.h"

#include "../utils/keyboard.h"

#define FOV 70.0f
#define NEAR_PLANE 0.1f
#define FAR_PLANE 1000.0f

void Camera::createProjectionMatrix(glm::mat4 &out) {
	out = glm::perspective(FOV, Display::getAspectRatio(), NEAR_PLANE, FAR_PLANE);
}

Camera::Camera() : position(glm::vec3(0, 0, 0)) {
	
}

Camera::~Camera() {

}

void Camera::move() {
	if (keyboard::isKeyDown(GLFW_KEY_W)) {
		position.z -= 0.02f;
	}
	else if (keyboard::isKeyDown(GLFW_KEY_S)) {
		position.z += 0.02f;
	}
	
	if (keyboard::isKeyDown(GLFW_KEY_A)) {
		position.x -= 0.02f;
	}
	else if (keyboard::isKeyDown(GLFW_KEY_D)) {
		position.x += 0.02f;
	}

	if (keyboard::isKeyDown(GLFW_KEY_SPACE)) {
		position.y += 0.02f;
	}
	else if (keyboard::isKeyDown(GLFW_KEY_LEFT_SHIFT)) {
		position.y -= 0.02f;
	}
}

void Camera::createViewMatrix(glm::mat4 &out) const {
	out = glm::lookAt(position, position + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
}
