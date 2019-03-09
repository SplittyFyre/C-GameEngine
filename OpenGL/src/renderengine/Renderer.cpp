#include <GL/glew.h>
#include "Renderer.h"
#include "../utils/sfmath.h"
#include "Camera.h"
#include <stdio.h>

namespace Renderer {

	void init(EntityShader &shader) {
		glm::mat4 pm;
		Camera::createProjectionMatrix(pm);
		shader.start();
		shader.loadProjectionMatrix(pm);
		shader.stop();
	}

	void prepare() {
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(48 / 255.0f, 10 / 255.0f, 36 / 255.0f, 1);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}
	
	void render(Entity &entity, const EntityShader &shader) {

		uint enableVAATo = 2;

		const TexturedModel &model = entity.getModel();
		const RawModel &raw = model.rawModel;
		glBindVertexArray(raw.vaoid);

		for (int i = 0; i <= enableVAATo; i++)	glEnableVertexAttribArray(i);

		glm::mat4 transformationMatrix;
		sfmath::createTransformationMatrix(transformationMatrix, entity.getPosition(), entity.getRotation(), entity.getScale());
		
		shader.loadTransformationMatrix(transformationMatrix);

		const ModelTexture &texture = model.texture;
		shader.loadShineVariables(texture.shineDamper, texture.reflectivity);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, model.texture.ID);
		glDrawElements(GL_TRIANGLES, raw.vtxcnt, GL_UNSIGNED_INT, 0);

		for (int i = 0; i <= enableVAATo; i++)	glDisableVertexAttribArray(i);

		glBindVertexArray(0);
	}
}
