#pragma once

#include "../utils/mytypes.h"

struct RawModel {
	uint vaoid, vtxcnt;
	RawModel(uint vaoidin, uint vtxcntin) : vaoid(vaoidin), vtxcnt(vtxcntin) {};
	RawModel();
};

struct ModelTexture {
	uint ID;
	float shineDamper = 1, reflectivity = 0;
	ModelTexture(uint texid) : ID(texid) {}
};

struct TexturedModel {
	RawModel rawModel;
	ModelTexture texture;
	TexturedModel(RawModel raw, ModelTexture tex) : rawModel(raw), texture(tex) {}
};
