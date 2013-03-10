#ifndef Hex_h__
#define Hex_h__

#include <string>
#include <vector>
#include "Point.h"
#include "Common.h"

class HexVertex;
class HalfQuad;

class Hex {
public:

	Hex(int id, int index, HexVertex *vers[8], std::string& property = std::string(""));
	~Hex();
	int id() { return m_id; }
	int& index() { return m_index; }
	HexVertex *&vertex(int i) { return m_vers[i]; }

	std::string& property() { return m_property; }
	HalfQuad *halfquad(int i) { return m_halfquads[i]; }
	Point center() const { return m_center; }
	bool& isBoundary() { return m_boundary; }
	std::vector<HalfQuad*> boundaryHalfQuads;

private:
	bool m_boundary;
	int m_id;
	int m_index;
	HexVertex *m_vers[8];		
	HalfQuad *m_halfquads[6];
	std::string m_property;
	Point m_center;	
};
#endif // Hex_h__