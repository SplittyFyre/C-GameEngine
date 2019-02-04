#include "EntityShader.h"

#define VERTEX_FILE "src/entities/shaders/vertexShader.glsl"
#define FRAGMENT_FILE "src/entities/shaders/fragmentShader.glsl"

void EntityShader::bindAttributes() {
	bindAttrib(0, "position");
}

EntityShader::EntityShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE) {}

