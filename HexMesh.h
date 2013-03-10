#ifndef HexMesh_h__
#define HexMesh_h__

#include <hash_map>
#include <sstream>
#include <vector>

class HexVertex;
class HalfQuad;
class Quad;
class Hex;

class HexMesh {
public:
	HexMesh();
	~HexMesh();

	void read(const char *filename);
	void write(const char *filename);
	void write2(const char *filename);
	std::vector<HalfQuad *>& getBoudnary() { return m_boundary_halfquads; }
	std::vector<Quad*>& getQuads() { return m_quads; }	

private:
	HexVertex *createHexVertex(std::stringstream &ss);
	Hex* createHex(std::stringstream &ss);
	
	void normalize();


private:
	int m_next_vid;
	int m_next_hid;
	stdext::hash_map<int, HexVertex *>		id2Ver;			
	stdext::hash_map<int, Hex *>			id2Hex;		
	std::vector<HalfQuad *> m_boundary_halfquads;
	std::vector<Quad*> m_quads;

	friend class HexMeshHexIterator;
	friend class HexMeshVertexIterator;
	friend class HexMeshQuadIterator;
};

#endif // HexMesh_h__