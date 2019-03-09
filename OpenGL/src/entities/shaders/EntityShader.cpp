#include "EntityShader.h"
#include <stdio.h>

#define VERTEX_FILE "src/entities/shaders/vertexShader.glsl"
#define FRAGMENT_FILE "src/entities/shaders/fragmentShader.glsl"

void EntityShader::bindAttributes() {
	bindAttrib(0, "position");
	bindAttrib(1, "textureCoords");
	bindAttrib(2, "normal");
}

void EntityShader::getAllUniformLocations() {

	addUniformVariable("transformationMatrix");
	addUniformVariable("projectionMatrix");
	addUniformVariable("viewMatrix");

	addUniformVariable("lightPos");
	addUniformVariable("lightColour");

	addUniformVariable("shineDamper");
	addUniformVariable("reflectivity");

} 

EntityShader::EntityShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE) {
	bindAttributes();
	manualLink();
	getAllUniformLocations();
}

//***********************************

void EntityShader::loadTransformationMatrix(const glm::mat4 &matrix) const {
	loadMatrix(uniformLocationOf("transformationMatrix"), matrix);
}

void EntityShader::loadProjectionMatrix(const glm::mat4 &matrix) const {
	loadMatrix(uniformLocationOf("projectionMatrix"), matrix);
}

void EntityShader::loadViewMatrix(const Camera &camera) const {
	glm::mat4 mat;
	camera.createViewMatrix(mat);
	loadMatrix(uniformLocationOf("viewMatrix"), mat);
}

void EntityShader::loadLight(const Light &light) const {
	loadvector(uniformLocationOf("lightPos"), light.getPosition());
	loadvector(uniformLocationOf("lightColour"), light.getColour());
}

void EntityShader::loadShineVariables(float damper, float reflectivity) const {
	loadfloat(uniformLocationOf("shineDamper"), damper);
	loadfloat(uniformLocationOf("reflectivity"), reflectivity);
}


