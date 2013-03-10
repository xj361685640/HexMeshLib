#ifndef Quad_h__
#define Quad_h__

#include "Point.h"
class HalfQuad;
class HexEdge;

class Quad {
public:
	Quad(HalfQuad *halfquad);
	~Quad();
	HalfQuad *& halfquad(int i) { return m_halfquads[i]; }
	HexEdge *& hexedge(int i) { return m_edges[i]; }	
	Point center() const { return m_center;  }
	int &index() { return m_index; }
private:
	HalfQuad *m_halfquads[2];	
	HexEdge *m_edges[4];
	Point m_center;
	int m_index;
};
#endif // Quad_h__