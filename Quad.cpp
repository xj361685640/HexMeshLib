#include "Quad.h"

Quad::Quad(HalfQuad *halfquad) {
	m_halfquads[0] = halfquad;
	m_halfquads[1] = 0;
}

Quad::~Quad() {

}