#pragma once
#include "../../renderengine/shaders/ShaderProgram.h"
#include "../../renderengine/Camera.h"
#include "../../renderengine/Light.h"

class EntityShader : public ShaderProgram {
public:
	EntityShader();
	void loadTransformationMatrix(const glm::mat4 &matrix) const;
	void loadProjectionMatrix(const glm::mat4 &matrix) const;
	void loadViewMatrix(const Camera &camera) const;

	void loadLight(const Light &light) const;
	void loadShineVariables(float damper, float reflectivity) const;

private:
	
protected:
	void bindAttributes() override;
	void getAllUniformLocations() override;
};

