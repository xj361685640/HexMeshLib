#ifndef Hex_h__
#define Hex_h__

#include <string>

class HexVertex;
class HalfQuad;

class Hex {
public:
	enum { FRONT, UP, BACK, DOWN, RIGHT, LEFT };

	Hex(int id, int index, HexVertex *vers[8], std::string& property = std::string(""));
	~Hex();
	int id() { return m_id; }
	int& index() { return m_index; }
	HexVertex *vertex(int i) { return m_vers[i]; }
	std::string& property() { return m_property; }
	HalfQuad *halfquad(int i) { return m_halfquads[i]; }

private:
	HalfQuad *createHalfQuad(HexVertex *vers[4]);
private:
	int m_id;
	int m_index;
	HexVertex *m_vers[8];		
	HalfQuad *m_halfquads[6];
	std::string m_property;
	
};
#endif // Hex_h__