#include "rotate_vector.hpp"

#include "basemath.h"

#include "cdisk.h"

using namespace agl;
using namespace bu;

void CDisk::initGeometry() {
    m_mesh.Clear();

    const aVec3 orientation(0.0, 0.0, m_radius);
    const aVec3 normal(0.0, 1.0, 0.0);

    const double step = TWO_PI<double> / (double)m_subdivision;
    const aVec3 centralPoint(0.0, 0.0, 0.0);
    for (int i = 0; i < m_subdivision; ++i) {

        aVec3 pntEdge[2];
        for (int j = 0; j < 2; ++j) {
            pntEdge[j] = glm::rotate<float>(orientation, step * (double)(j + i), normal);
        }

        m_mesh.AddVertexCoord(centralPoint);
        m_mesh.AddVertexCoord(pntEdge[0]);
        m_mesh.AddVertexCoord(pntEdge[1]);
    }

    m_mesh.SetMode(CMesh::eTriangles);
}

CDisk::CDisk() :
    m_radius(1.0),
    m_subdivision(10) {

    initGeometry();

    m_material.SetShaderProgram("phong");
}

void CDisk::SetRadius(double val_) {
    if (val_ > 0 && !Equal<double>(val_, m_radius)) {
        m_radius = val_;
        initGeometry();
    }
}

double CDisk::GetRadius() const {
    return m_radius;
}

void CDisk::SetSubdiv(uint val_) {
    if (val_ > 0 && (val_ != m_subdivision)) {
        m_subdivision = val_;
        initGeometry();
    }
}

uint CDisk::GetSubdiv() const {
    return m_subdivision;
}

CMaterial* CDisk::GetMaterial() {
    return &m_material;
}
