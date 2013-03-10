#include "Hex.h"
#include "HexVertex.h"
#include "HalfQuad.h"

Hex::Hex(int id, int index, HexVertex *vers[8], std::string& property)
: m_id(id), m_index(index), m_property(property),  m_boundary(false)
{
	
	for (int i = 0; i < 8; ++i) {
		m_vers[i] = vers[i];
		m_center += vers[i]->point();
	}

	m_center /= 8.0;

	static int fv_order[][4] = {
		1, 0, 4, 5,
		3, 1, 5, 7,
		3, 7, 6, 2,
		0, 2, 6, 4,
		5, 4, 6, 7,
		1, 3, 2, 0,
	};


	for (int i = 0; i < MAX_ORIENTATION; ++i) {
		HexVertex *vers[4];
		for (int j = 0; j < 4; ++j) {
			vers[j] = m_vers[fv_order[i][j]];
		}

		HalfQuad *halfquad = new HalfQuad(vers, ORIENTATION(i));
		m_halfquads[i] = halfquad;
		halfquad->hex() = this;
	}
}

Hex::~Hex() {

}

