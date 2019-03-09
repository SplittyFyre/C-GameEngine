#include "DisplayManager.h"
#include <iostream>
#include <stdio.h>

namespace Display {

	GLFWwindow *window;

	GLFWwindow *getWindow() {
		return window;
	}


	int displayWidth = INITIAL_WIDTH, displayHeight = INITIAL_HEIGHT;


	void windowRefeshCallback(GLFWwindow *window) {
		glfwGetFramebufferSize(window, &displayWidth, &displayHeight);
		glViewport(0, 0, displayWidth, displayHeight);
	}

	float getAspectRatio() {
		return (float) displayWidth / (float) displayHeight;
	}
	
	void createDisplay() {
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, CONTEXT_MAJOR_VAL);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, CONTEXT_MINOR_VAL);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

		window = glfwCreateWindow(INITIAL_WIDTH, INITIAL_HEIGHT, "CTrek Engine", nullptr, nullptr);
		if (window == nullptr) {
			std::cerr << "Failed to create GLFW window\n";
			glfwTerminate();
			exit(1);
		}
		
		glfwMakeContextCurrent(window);

		// pretty much just resize
		glfwSetWindowRefreshCallback(window, windowRefeshCallback);

		// init glew
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK) {
			std::cerr << "Failed to initialize glew\n";
			exit(1);
		}

		glViewport(0, 0, INITIAL_WIDTH, INITIAL_HEIGHT);

	}

	void updateDisplay() {
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void closeDisplay() {
		glfwTerminate();
	}


}