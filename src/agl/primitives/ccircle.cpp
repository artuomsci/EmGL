#include "rotate_vector.hpp"

#include "basemath.h"
#include "ccircle.h"

using namespace agl;
using namespace bu;

CCircle::CCircle() :
    m_radius(1.0),
    m_subdivision(10) {

    initGeometry();

    m_material.SetShaderProgram("diffuse");
}

void CCircle::SetRadius(double val_) {
    if (val_ > 0 && !Equal<double>(val_, m_radius)) {
        m_radius = val_;
        initGeometry();
    }
}

double CCircle::GetRadius() const {
    return m_radius;
}

void CCircle::SetSubdiv(uint val_) {
    if (val_ > 0 && (val_ != m_subdivision)) {
        m_subdivision = val_;
        initGeometry();
    }
}

int CCircle::GetSubdiv() const {
    return m_subdivision;
}

CMaterial* CCircle::GetMaterial() {
    return &m_material;
}

void CCircle::initGeometry() {
    m_mesh.Clear();

    std::vector<aVec3> vArr;

    aVec3 orientation(0.0, 0.0, m_radius);
    aVec3 normal(0.0, 1.0, 0.0);

    double step = TWO_PI<double> / (double)m_subdivision;
    aVec3 rotVec;
    for (int i = 0; i < m_subdivision; ++i) {
        rotVec = glm::rotate<float>(orientation, step * (double)i, normal);
        vArr.push_back(rotVec);
        if (i != 0)
            vArr.push_back(rotVec);
    }
    vArr.push_back(vArr[0]);

    for (int i = 0; i < vArr.size(); ++i)
        m_mesh.AddVertexCoord(vArr[i]);

    m_mesh.SetMode(CMesh::eLines);
}

