#ifndef HexVertex_h__
#define HexVertex_h__

#include "Point.h"
#include <string>

class HexVertex {
public:
	HexVertex(int id, int index, Point& pos, std::string& property = std::string(""));
	~HexVertex();
	int id() { return m_id; }
	int& index() { return m_index; }
	Point& point() { return m_point; }
	std::string& property() { return m_property; }

private:
	int m_id;
	int m_index;
	Point m_point;
	std::string m_property;
};
#endif // HexVertex_h__