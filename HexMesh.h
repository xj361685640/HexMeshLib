#ifndef HexMesh_h__
#define HexMesh_h__

#include <hash_map>
#include <sstream>

class HexVertex;
class Hex;

class HexMesh {
public:
	HexMesh();
	~HexMesh();

	void read(const char *filename);
	void write(const char *filename);

private:
	HexVertex *createHexVertex(std::stringstream &ss);
	Hex* createHex(std::stringstream &ss);

private:
	int m_next_vid;
	int m_next_hid;
	stdext::hash_map<int, HexVertex *>		id2Ver;			
	stdext::hash_map<int, Hex *>			id2Hex;		
};
#endif // HexMesh_h__