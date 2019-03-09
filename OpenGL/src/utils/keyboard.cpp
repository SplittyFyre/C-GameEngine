#include "keyboard.h"

namespace keyboard {
	bool isKeyDown(int key) {
		return glfwGetKey(glfwGetCurrentContext(), key) == GLFW_PRESS;
	}
}