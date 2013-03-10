#ifndef HexVertex_h__
#define HexVertex_h__

#include "Point.h"
#include <string>
#include <vector>

class Hex;

class HexVertex {
public:
	HexVertex(int id, int index, Point& pos, std::string& property = std::string(""));
	~HexVertex();
	int id() { return m_id; }
	int& index() { return m_index; }
	void add(Hex* hex) { m_hexes.push_back(hex); }
	Point& point() { return m_point; }
	std::string& property() { return m_property; }
	
private:
	int m_id;
	int m_index;
	Point m_point;
	std::string m_property;
	std::vector<Hex*> m_hexes;
};
#endif // HexVertex_h__