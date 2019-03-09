#pragma once

#include "models.h"
#include "../entities/Entity.h"
#include "../entities/shaders/EntityShader.h"

namespace Renderer {
	void init(EntityShader &shader);
	void prepare();
	void render(Entity &entity, const EntityShader &shader);
}