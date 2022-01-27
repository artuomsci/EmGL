#include "rotate_vector.hpp"

#include "basemath.h"
#include "ccylinder.h"

using namespace agl;
using namespace bu;

void CCylinder::initGeometry() {
    m_mesh.Clear();

    const aVec3 orientation(0.0, 0.0, m_radius);
    const aVec3 normal(0.0, 1.0, 0.0);

    const double step = TWO_PI<double> / (double)m_subdivision;
    const aVec3 centralPoint(0.0, 0.0, 0.0);
    const aVec3 centralPointTop(0.0, m_height, 0.0);
    for (int i = 0; i < m_subdivision; ++i) {

        aVec3 pntBottom[2];
        for (int j = 0; j < 2; ++j) {
            pntBottom[j] = glm::rotate<float>(orientation, step * (double)(j + i), normal);
        }

        // cylinder bottom
        m_mesh.AddVertexCoord(centralPoint);
        m_mesh.AddVertexCoord(pntBottom[1]);
        m_mesh.AddVertexCoord(pntBottom[0]);

        m_mesh.AddNormalCoord(aVec3(0.0, -1.0, 0.0));
        m_mesh.AddNormalCoord(aVec3(0.0, -1.0, 0.0));
        m_mesh.AddNormalCoord(aVec3(0.0, -1.0, 0.0));

        // cylinder top
        aVec3 pntTop[2];
        pntTop[0] = pntBottom[0];
        pntTop[1] = pntBottom[1];
        pntTop[0].y = m_height;
        pntTop[1].y = m_height;

        m_mesh.AddVertexCoord(centralPointTop);
        m_mesh.AddVertexCoord(pntTop[0]);
        m_mesh.AddVertexCoord(pntTop[1]);

            m_mesh.AddNormalCoord(aVec3(0.0, 1.0, 0.0));
            m_mesh.AddNormalCoord(aVec3(0.0, 1.0, 0.0));
            m_mesh.AddNormalCoord(aVec3(0.0, 1.0, 0.0));

        // cylinder wall
        m_mesh.AddVertexCoord(pntBottom[0]);
        m_mesh.AddVertexCoord(pntBottom[1]);
        m_mesh.AddVertexCoord(pntTop[0]);

            m_mesh.AddNormalCoord(glm::normalize(pntBottom[0]));
            m_mesh.AddNormalCoord(glm::normalize(pntBottom[1]));
            m_mesh.AddNormalCoord(glm::normalize(pntBottom[0]));

        m_mesh.AddVertexCoord(pntTop[1]);
        m_mesh.AddVertexCoord(pntTop[0]);
        m_mesh.AddVertexCoord(pntBottom[1]);

            m_mesh.AddNormalCoord(glm::normalize(pntBottom[1]));
            m_mesh.AddNormalCoord(glm::normalize(pntBottom[0]));
            m_mesh.AddNormalCoord(glm::normalize(pntBottom[1]));
    }

    m_mesh.SetMode(CMesh::eTriangles);
}

CCylinder::CCylinder() :
    m_radius(1.0),
    m_height(1.0),
    m_subdivision(10) {

    initGeometry();

    m_material.SetShaderProgram("phong");
}

CCylinder::~CCylinder() {
}

void CCylinder::SetRadius(double val_) {
    if (val_ > 0 && !Equal<double>(val_, m_radius)) {
        m_radius = val_;
        initGeometry();
    }
}

double CCylinder::GetRadius() const {
    return m_radius;
}

void CCylinder::SetHeight(double val_) {
    if (val_ > 0 && !Equal<double>(val_, m_height)) {
        m_height = val_;
        initGeometry();
    }
}

double CCylinder::GetHeight() const {
    return m_height;
}

void CCylinder::SetSubdiv(uint val_) {
    if (val_ > 0 && (val_ != m_subdivision)) {
        m_subdivision = val_;
        initGeometry();
    }
}

uint CCylinder::GetSubdiv() const {
    return m_subdivision;
}

CMaterial* CCylinder::GetMaterial() {
    return &m_material;
}
