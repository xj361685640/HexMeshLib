#include "HalfQuad.h"

HalfQuad::HalfQuad(HexVertex *vers[4]) {
	for (int i = 0; i < 4; ++i) {
		m_vers[i] = vers[i];
	}

	
}

HalfQuad::~HalfQuad() {
	
}
