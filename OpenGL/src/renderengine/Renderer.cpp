#include <GL/glew.h>
#include "Renderer.h"

namespace Renderer {
	void prepare() {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1, 0, 1, 1);
	}
	
	void render(RawModel model) {
		glBindVertexArray(model.vaoid);
		glEnableVertexAttribArray(0);
		glDrawElements(GL_TRIANGLES, model.vtxcnt, GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);
	}
}
