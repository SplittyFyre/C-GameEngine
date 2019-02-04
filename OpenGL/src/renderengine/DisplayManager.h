#pragma once

#define INITIAL_WIDTH 1280
#define INITIAL_HEIGHT 720
#define FPS_CAP 120

#define CONTEXT_MAJOR_VAL 3
#define	CONTEXT_MINOR_VAL 3

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace display {

	void createDisplay();
	void updateDisplay();
	void closeDisplay();

	GLFWwindow *getWindow();

}
