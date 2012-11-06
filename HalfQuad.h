#ifndef HalfQuad_h__
#define HalfQuad_h__

class HexVertex;
class Quad;
class Hex;

class HalfQuad {
public:
	HalfQuad(HexVertex *vers[4]);
	~HalfQuad();
	Hex *&hex() { return m_hex; }
	Quad*& quad()  { return m_quad; }
	HexVertex *vertex(int i) { return m_vers[i]; }

private:
	Quad *m_quad;
	HexVertex *m_vers[4];
	Hex *m_hex;
};

#endif // HalfQuad_h__