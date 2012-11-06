#ifndef Quad_h__
#define Quad_h__

class HalfQuad;
class HexEdge;

class Quad {
public:
	Quad(HalfQuad *halfquad);
	~Quad();
	HalfQuad *& halfquad(int i) { return m_halfquads[i]; }
	HexEdge *& hexedge(int i) { return m_edges[i]; }	
private:
	HalfQuad *m_halfquads[2];	
	HexEdge *m_edges[4];
};
#endif // Quad_h__