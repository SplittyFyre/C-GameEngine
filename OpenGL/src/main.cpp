#include <iostream>
#include "renderengine/DisplayManager.h"
#include "renderengine/Loader.h"
#include "renderengine/Renderer.h"
#include "entities\shaders\EntityShader.h"
#include "entities\Entity.h"
#include <vector>
#include <stdlib.h>
#include <glm/glm/vec3.hpp>
#include "utils/keyboard.h"
#include "renderengine/Camera.h"
#include "renderengine/obj/objparser.h"

int main(void) {

	Display::createDisplay();
	
	//RawModel model = objparser::loadObjModel("warship_voyager_model");
	//ModelTexture texture(Loader::loadTexture("warship_voyager_texture"));
	RawModel model = objparser::loadObjModel("dragon");
	ModelTexture texture(Loader::loadTexture("white"));
	texture.shineDamper = 10;
	texture.reflectivity = 1;
	TexturedModel full(model, texture);

	Entity entity(full, glm::vec3(0, 0, -25), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	Light light(glm::vec3(0, 0, -20), glm::vec3(1.3f, 1.3f, 1.3f)); 

	puts("curr dir:");
	system("cd");
	puts("");

	EntityShader shader;
	Renderer::init(shader);

	Camera camera;
	
	while (!glfwWindowShouldClose(Display::getWindow())) {

		entity.rotate(0, 1, 0);

		camera.move();
		Renderer::prepare();

		shader.start();
		shader.loadLight(light);
		shader.loadViewMatrix(camera);
		Renderer::render(entity, shader);

		shader.stop();

		Display::updateDisplay();
	}

	Loader::cleanUp();
	Display::closeDisplay();

	return 0;
}