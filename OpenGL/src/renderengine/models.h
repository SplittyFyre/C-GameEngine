#pragma once

#include "../utils/mytypes.h"

struct RawModel {
	uint vaoid, vtxcnt;
	RawModel(uint vaoidin, uint vtxcntin) : vaoid(vaoidin), vtxcnt(vtxcntin) {}
};
