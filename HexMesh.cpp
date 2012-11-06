#include "Hex.h"
#include "Quad.h"
#include "HexEdge.h"
#include "HexMesh.h"
#include "HalfQuad.h"
#include "HexVertex.h"
#include "HexMeshUtils.h"
#include <iostream>
#include <fstream>
#include <map>

HexMesh::HexMesh() {

}

HexMesh::~HexMesh() {

}


void HexMesh::read(const char *filename) {
	
	std::ifstream input(filename);
	
	while(input.good()) {
		std::string line;
		getline(input, line);
		if (line.empty()) {
			continue;
		}

		std::stringstream ss(line);

		std::string title, remain;
		ss >> title;

		if (title == "Vertex") {
			HexVertex *tv = createHexVertex(ss);
			id2Ver[tv->id()] = tv;
		} else if (title == "Tetrahedron") {
			Hex *hex = createHex(ss);
			id2Hex[hex->id()] = hex;
		}
	}

	input.close();

	id2Ver.rehash(id2Ver.size());
	id2Hex.rehash(id2Hex.size());
	
	m_next_vid = id2Ver.size();
	m_next_hid = id2Hex.size();
	
	//link vertex to tetra
	/*for (stdext::hash_map<int, Hex*>::iterator b = id2Hex.begin(), e = id2Hex.end(); b != e; ++b) {
		Hex *tet = (*b).second;
		for (int i = 0; i < 4; ++i) {
			HexVertex *hv = tet->vertex(i);
			tv->add(tet);
		}
	}*/

	/*std::vector<TetHalfFace*> halffaces;
	for (stdext::hash_map<int, Tetra*>::iterator b = id2Tetra.begin(), e = id2Tetra.end(); b != e; ++b) {
		Tetra *tet = (*b).second;
		for (int i = 0; i < 4; ++i) {
			TetHalfFace *hf = tet->halfface(i);
			halffaces.push_back(hf);
		}
	}*/

//	std::vector<TetFace*> faces;
//	TetMeshUtility::buildFaces(halffaces, faces);

//	std::vector<TetEdge*> edges;
	//TetMeshUtility::buildEdges(faces, edges);


	//build quads
	std::map<quadlet, Quad*> quadmap;
	for (stdext::hash_map<int, Hex*>::iterator b = id2Hex.begin(), e = id2Hex.end(); b != e; ++b) {
		Hex *hex = (*b).second;
		
		for (int i = 0; i < 6; ++i) {
			HalfQuad *halfquad = hex->halfquad(i);	
			quadlet qlet = construct_quad(halfquad);
				
			Quad *quad = quadmap[qlet];

			if (!quad) {
				quad = new Quad(halfquad);				
				quadmap[qlet] = quad;
			} else {
				if (quad->halfquad(1)) {
					std::cout << "non-manifold!\n";
					exit(-1);
				}
				quad->halfquad(1) = halfquad;
				halfquad->quad() = quad;
			}
		}
			
	}


	//build edges;
	std::map<pairint, HexEdge*> edgemap;
	for (std::map<quadlet, Quad*>::iterator b = quadmap.begin(), e = quadmap.end(); b != e; ++b) {
		Quad *quad = (*b).second;
		HalfQuad *halfquad = quad->halfquad(0);
		for (int i = 0; i < 4; ++i) {
			HexVertex *v0 = halfquad->vertex(i);
			HexVertex *v1 = halfquad->vertex((i+1) % 4);

			pairint p = construct_pairint(v0, v1);
			HexEdge *hedge = edgemap[p];

			if (!hedge) {
				HexEdge *hedge = new HexEdge(v0, v1);
				edgemap[p] = hedge;
			} 

			quad->hexedge(i) = hedge;
			hedge->add(quad);
		}
	}

	

}


void HexMesh::write(const char *filename) {
	std::ofstream output(filename);
	


	output.close();
}


HexVertex * HexMesh::createHexVertex(std::stringstream &ss) {
	int id;
	Point pos;
	std::string property;
	ss >> id >> pos.v[0] >> pos.v[1] >> pos.v[2];
	getline(ss, property);
	HexVertex *v = new HexVertex(id, id2Ver.size(), pos, property);
	return v;
}

Hex*  HexMesh::createHex(std::stringstream &ss) {
	int id;
	int vids[8];
	std::string property;
	ss >> id >> vids[0] >> vids[1] >> vids[2] >> vids[3] >> vids[4] >> vids[5] >> vids[6] >> vids[7];
	HexVertex *vers[8];
	for (int i = 0; i < 8; ++i) {
		vers[i] = id2Ver[vids[i]];
	}
	getline(ss, property);
	Hex *hex = new Hex(id, id2Hex.size(), vers, property);
	return hex;
}

