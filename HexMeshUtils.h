#ifndef HexMeshUtils_h__
#define HexMeshUtils_h__

#include "HalfQuad.h"
#include <algorithm>


typedef std::pair<int, int> pairint;

inline pairint construct_pairint(HexVertex *v0, HexVertex *v1) {
	int vid0 = v0->id();
	int vid1 = v1->id();
	
	return vid0 < vid1 ? std::make_pair(vid0, vid1) : std::make_pair(vid1, vid0);
}

typedef std::pair<int, std::pair<int, std::pair<int, int> > > quadlet;

inline quadlet construct_quad(HalfQuad *halfquad) {
	int vids[4] = {halfquad->vertex(0)->id(), halfquad->vertex(1)->id(), halfquad->vertex(2)->id(), halfquad->vertex(3)->id()};
	/*int mn = std::min(vids[0], std::min(vids[1], vids[2]));
	int mx = std::max(vids[0], std::max(vids[1], vids[2]));
	int mid = vids[0] + vids[1] + vids[2] - mn -mx;*/
	
	std::sort(vids, vids + 4);
	return make_pair(vids[0], std::make_pair(vids[1], std::make_pair(vids[2], vids[3])));
}



#endif // HexMeshUtils_h__