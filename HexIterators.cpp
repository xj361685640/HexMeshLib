#include "HexIterators.h"
#include "HexVertex.h"
#include "HalfQuad.h"
#include "HexEdge.h"
#include "Quad.h"

HexEdgeHexIterator::HexEdgeHexIterator(HexEdge *hedge) {
	for (size_t i = 0; i < hedge->m_quads.size(); ++i) {
		Quad *quad = hedge->m_quads[i];
		for (int j = 0; j < 2; ++j) {
			HalfQuad *halfquad = quad->halfquad(j);
			if (!halfquad) {
				Hex *hex = halfquad->hex();
				m_hexes.insert(hex);
			}
		}
	}

	m_it = m_hexes.begin();
}


HexEdgeHexIterator::~HexEdgeHexIterator() {
	
}