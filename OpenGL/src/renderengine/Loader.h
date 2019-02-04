#pragma once

#include <vector>
#include "models.h"

namespace Loader {
	RawModel loadtoVAO(std::vector<float> positions, std::vector<int> indices);
	void cleanUp();
}