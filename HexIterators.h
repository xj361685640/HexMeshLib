#ifndef HexIterators_h__
#define HexIterators_h__

#include <set>

class HexEdge;
class Hex;

class HexEdgeHexIterator {
public:
	HexEdgeHexIterator(HexEdge *hedge);
	~HexEdgeHexIterator();

	void operator ++() {
		++m_it;
	}	

	Hex* operator* () {
		return *m_it;
	}

	bool end() {
		return m_it == m_hexes.end();	
	}

private:
	std::set<Hex*> m_hexes;
	std::set<Hex*>::iterator m_it;
};

#endif // HexIterators_h__