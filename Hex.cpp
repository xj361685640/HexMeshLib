#include "Hex.h"
#include "HalfQuad.h"

Hex::Hex(int id, int index, HexVertex *vers[8], std::string& property)
: m_id(id), m_index(index), m_property(property) 
{
	for (int i = 0; i < 8; ++i) {
		m_vers[i] = vers[i];
	}
	static int fv_order[][4] = {
		1, 0, 4, 5,
		3, 1, 5, 7,
		3, 7, 6, 2,
		0, 2, 6, 4,
		5, 4, 6, 7,
		1, 3, 2, 0,
	};


	for (size_t i = 0; i < 6; ++i) {
		HexVertex *vers[4];
		for (int j = 0; j < 4; ++j) {
			vers[j] = m_vers[fv_order[i][j]];
		}

		HalfQuad *halfquad = createHalfQuad(vers);
		m_halfquads[i] = halfquad;
		halfquad->hex() = this;
	}
}

Hex::~Hex() {

}


HalfQuad * Hex::createHalfQuad(HexVertex *vers[4]) {
	return new HalfQuad(vers);
}