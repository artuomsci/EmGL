#include "rotate_vector.hpp"

#include "basemath.h"
#include "ccone.h"

using namespace agl;
using namespace bu;

void CCone::initGeometry() {
    m_mesh.Clear();

    const aVec3 orientation(0.0, 0.0, m_radius);
    const aVec3 normal(0.0, 1.0, 0.0);

    const double wallAngle = HALF_PI<double> - atan(m_height / m_radius);
    const double step = TWO_PI<double> / (double)m_subdivRadial;
    const aVec3 centralPoint(0.0, 0.0, 0.0);
    const aVec3 centralPointTop(0.0, m_height, 0.0);

    for (int i = 0; i < m_subdivRadial; ++i) {

        aVec3 pntBottom[2];
        for (int j = 0; j < 2; ++j)
            pntBottom[j] = glm::rotate<float>(orientation, step * (double)(j + i), normal);

        // rotation axes for normals
        const aVec3 r0 = glm::cross(pntBottom[0], normal);
        const aVec3 r1 = glm::cross(pntBottom[1], normal);

        // side normals
        const aVec3 n0 = glm::normalize(glm::rotate<float>(pntBottom[0], wallAngle, r0));
        const aVec3 n1 = glm::normalize(glm::rotate<float>(pntBottom[1], wallAngle, r1));
        const aVec3 midNormal = glm::normalize(n0 + n1);

        //-------------- forming triangles ------------------

        // cone bottom
        m_mesh.AddVertexCoord(centralPoint);
        m_mesh.AddVertexCoord(pntBottom[1]);
        m_mesh.AddVertexCoord(pntBottom[0]);

        // bottom normals
        m_mesh.AddNormalCoord(aVec3(0.0, -1.0, 0.0));
        m_mesh.AddNormalCoord(aVec3(0.0, -1.0, 0.0));
        m_mesh.AddNormalCoord(aVec3(0.0, -1.0, 0.0));

        aVec3 midWall[2];
        midWall[0] = (centralPointTop - pntBottom[0]) * (1.0f / m_subdivConcentric);
        midWall[1] = (centralPointTop - pntBottom[1]) * (1.0f / m_subdivConcentric);

        for (int k = 0; k < m_subdivConcentric - 1; ++k) {

            aVec3 v0, v1, v2, v3;
            v0 = pntBottom[0] + midWall[0] * (float)k;
            v1 = pntBottom[1] + midWall[1] * (float)k;
            v2 = pntBottom[1] + midWall[1] * (float)(k + 1);
            v3 = pntBottom[0] + midWall[0] * (float)(k + 1);

            // cone sides triangles
            m_mesh.AddVertexCoord(v0);
            m_mesh.AddVertexCoord(v1);
            m_mesh.AddVertexCoord(v2);

                // cone sides normals
                m_mesh.AddNormalCoord(n0);
                m_mesh.AddNormalCoord(n1);
                m_mesh.AddNormalCoord(n1);

            // cone sides triangles
            m_mesh.AddVertexCoord(v2);
            m_mesh.AddVertexCoord(v3);
            m_mesh.AddVertexCoord(v0);

                // cone sides normals
                m_mesh.AddNormalCoord(n1);
                m_mesh.AddNormalCoord(n0);
                m_mesh.AddNormalCoord(n0);
        }

        // top cone side
        m_mesh.AddVertexCoord(pntBottom[0] + midWall[0] * float(m_subdivConcentric - 1));
        m_mesh.AddVertexCoord(pntBottom[1] + midWall[1] * float(m_subdivConcentric - 1));
        m_mesh.AddVertexCoord(centralPointTop);

            m_mesh.AddNormalCoord(n0);
            m_mesh.AddNormalCoord(n1);
            m_mesh.AddNormalCoord(midNormal);
    }

    m_mesh.SetMode(CMesh::eTriangles);
}

CCone::CCone() :
    m_radius(1.0),
    m_height(1.0),
    m_subdivRadial(10),
    m_subdivConcentric(10) {

    initGeometry();

    m_material.SetShaderProgram("phong");
}

void CCone::SetHeight(double val_) {
    if (val_ > 0 && !Equal<double>(val_, m_height)) {
        m_height = val_;
        initGeometry();
    }
}

double CCone::GetHeight() const {
    return m_height;
}

void CCone::SetRadius(double val_) {
    if (val_ > 0 && !Equal<double>(val_, m_radius)) {
        m_radius = val_;
        initGeometry();
    }
}

double CCone::GetRadius() const {
    return m_radius;
}

void CCone::SetUSubdiv(uint val_) {
    if (val_ > 0 && (val_ != m_subdivRadial)) {
        m_subdivRadial = val_;
        initGeometry();
    }
}

uint CCone::GetUSubdiv() const {
    return m_subdivRadial;
}

void CCone::SetVSubdiv(uint val_) {
    if (val_ > 0 && (val_ != m_subdivConcentric)) {
        m_subdivConcentric = val_;
        initGeometry();
    }
}

uint CCone::GetVSubdiv() const {
    return m_subdivConcentric;
}

CMaterial* CCone::GetMaterial() {
    return &m_material;
}
