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
		} else if (title == "Hex") {
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
	for (stdext::hash_map<int, Hex*>::iterator b = id2Hex.begin(), e = id2Hex.end(); b != e; ++b) {
		Hex *hex = (*b).second;
		for (int i = 0; i < 4; ++i) {
			HexVertex *hv = hex->vertex(i);
			hv->add(hex);
		}
	}


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
				quad->index() = m_quads.size();
				m_quads.push_back(quad);
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

	for(std::map<quadlet, Quad*>::iterator b = quadmap.begin(), e = quadmap.end(); b != e; ++b) {
		Quad *quad = (*b).second;
		if (!quad->halfquad(1)) {
			m_boundary_halfquads.push_back(quad->halfquad(0));
			quad->halfquad(0)->hex()->isBoundary() = true;
			quad->halfquad(0)->hex()->boundaryHalfQuads.push_back(quad->halfquad(0));
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
				hedge = new HexEdge(v0, v1);
				edgemap[p] = hedge;
			} 

			quad->hexedge(i) = hedge;
			hedge->add(quad);
		}
	}

	

}


void HexMesh::write(const char *filename) {
	std::ofstream output(filename);
	for (int i = 0; i < m_next_vid; ++i) {
		if (id2Ver.find(i) == id2Ver.end()) {
			continue;
		}
		
		HexVertex *v = id2Ver[i];
		Point pt = v->point();
		output << "Vertex " << i  << " " << pt[0] << " " << pt[1] << " " << pt[2] << " " << v->property() << "\n";
	}	

	for (int i = 0; i < m_next_hid; ++i) {
		if (id2Hex.find(i) == id2Hex.end()) {
			continue;
		}
		
		Hex *h = id2Hex[i];
		output << "Hex " << i  << " ";
		for (int j = 0; j < 8; ++j) {
			output  << h->vertex(j)->id() << " ";
		}
		output << h->property() << "\n";
	}	

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
	if (id2Hex.empty()) {
		normalize();
	}
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



void HexMesh::write2(const char *filename) {
	std::ofstream output(filename);
	for (int i = 0; i < m_next_vid; ++i) {
		if (id2Ver.find(i) == id2Ver.end()) {
			continue;
		}
		
		HexVertex *v = id2Ver[i];
		Point pt = v->point();
		output << "Vertex " << i  << " " << pt[0] << " " << pt[1] << " " << pt[2] << " " << v->property() << "\n";
	}	

	for (int i = 0; i < m_next_hid; ++i) {
		if (id2Hex.find(i) == id2Hex.end()) {
			continue;
		}
		
		Hex *h = id2Hex[i];
		output << "Hex " << i  << " ";
		output  << h->vertex(0)->id() << " " 
			<< h->vertex(1)->id() << " " 
			<< h->vertex(4)->id() << " " 
			<< h->vertex(5)->id() << " " 
			<< h->vertex(3)->id() << " " 
			<< h->vertex(2)->id() << " " 
			<< h->vertex(7)->id() << " " 
			<< h->vertex(6)->id() << " "; 

		output << h->property() << "\n";
	}	

	output.close();
}


void HexMesh::normalize() {
	//normalize
	Point center;
	int count = 0;
	for (stdext::hash_map<int, HexVertex *>::iterator b = id2Ver.begin(), e = id2Ver.end(); b != e; ++b) {
		HexVertex *v = (*b).second;
		center += v->point();	
		++count;
	}
	center /= count;
		
	double max_len = -1e10;
	for (stdext::hash_map<int, HexVertex *>::iterator b = id2Ver.begin(), e = id2Ver.end(); b != e; ++b) {
		HexVertex *v = (*b).second;
		double len = (v->point() - center).norm();
	
		if (len > max_len) {
			max_len = len;
		}
	}
	
	for (stdext::hash_map<int, HexVertex *>::iterator b = id2Ver.begin(), e = id2Ver.end(); b != e; ++b) {
		HexVertex *v = (*b).second;
		v->point() -= center;
		v->point() /= max_len;
	}
}