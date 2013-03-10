#ifndef HalfQuad_h__
#define HalfQuad_h__

#include "Common.h"

class HexVertex;
class Quad;
class Hex;

class HalfQuad {
public:
	HalfQuad(HexVertex *vers[4], ORIENTATION o);
	~HalfQuad();
	Hex *&hex() { return m_hex; }
	Quad*& quad()  { return m_quad; }
	HexVertex *vertex(int i) { return m_vers[i]; }
	ORIENTATION& orientation() { return m_orientation; }
private:
	Quad *m_quad;
	HexVertex *m_vers[4];
	Hex *m_hex;
	ORIENTATION m_orientation;
};

#endif // HalfQuad_h__