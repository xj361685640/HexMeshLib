#include "HexVertex.h"


HexVertex::HexVertex(int id, int index, Point& pos, std::string& property) :
m_id(id), m_index(index), m_point(pos), m_property(property)
{

}

HexVertex::~HexVertex() {

}