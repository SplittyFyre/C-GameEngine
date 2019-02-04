#include <iostream>
#include "renderengine/DisplayManager.h"
#include "renderengine/Loader.h"
#include "renderengine/Renderer.h"
#include "entities\shaders\EntityShader.h"
#include <vector>
#include <stdlib.h>

int main(void) {

	display::createDisplay();

	std::vector<float> vertices = {
		-0.5, 0.5f, 0,
		-0.5f, -0.5f, 0,
		0.5f, -0.5f, 0,
		0.5f, 0.5f, 0
	};

	std::vector<int> indices = {
		0, 1, 3,
		3, 1, 2
	};

	RawModel model = Loader::loadtoVAO(vertices, indices);

	puts("curr dir:");
	system("cd");
	system("dir");

	system("pause");

	EntityShader shader;
	
	while (!glfwWindowShouldClose(display::getWindow())) {
		
		Renderer::prepare();

		shader.start();
		
		Renderer::render(model);

		shader.stop();

		display::updateDisplay();
	}

	Loader::cleanUp();
	display::closeDisplay();

	return 0;
}