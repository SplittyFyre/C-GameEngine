#pragma once
#include "../../renderengine/shaders/ShaderProgram.h"

class EntityShader : public ShaderProgram {
public:
	EntityShader();
protected:
	void bindAttributes() override;
};

