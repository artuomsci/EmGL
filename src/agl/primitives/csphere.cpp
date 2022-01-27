#include "rotate_vector.hpp"

#include "basemath.h"

#include "csphere.h"

using namespace agl;
using namespace bu;

void CSphere::initGeometry() {
    m_mesh.Clear();

    const aVec3 orientation(0.0, 0.0, m_radius);
    const aVec3 axisLat(0.0, 1.0, 0.0);

    const double stepLat = TWO_PI<double> / (double)m_latSubdiv;
    const double stepLon = HALF_PI<double> / (double)m_longSubdiv;

    for (int i = 0; i < m_latSubdiv; ++i) {
        aVec3 ltEdge[2];
        for (int j = 0; j < 2; ++j)
            ltEdge[j] = glm::rotate<float>(orientation, stepLat * (double)(j + i), axisLat);

        aVec3 axisLon[2];
        axisLon[0] = glm::cross(ltEdge[0], axisLat);
        axisLon[1] = glm::cross(ltEdge[1], axisLat);

        for (int m = 0; m < m_longSubdiv; ++m) {
            aVec3 leftSide[2];
            for (int n = 0; n < 2; ++n)
                leftSide[n] = glm::rotate<float>(ltEdge[0], stepLon * (double)(n + m), axisLon[0]);
            aVec3 rightSide[2];
            for (int n = 0; n < 2; ++n)
                rightSide[n] = glm::rotate<float>(ltEdge[1], stepLon * (double)(n + m), axisLon[1]);

            //-------------- Top half -----------
            m_mesh.AddVertexCoord(leftSide[1]);
            m_mesh.AddVertexCoord(leftSide[0]);
            m_mesh.AddVertexCoord(rightSide[1]);

            m_mesh.AddNormalCoord(glm::normalize(leftSide[1]));
            m_mesh.AddNormalCoord(glm::normalize(leftSide[0]));
            m_mesh.AddNormalCoord(glm::normalize(rightSide[1]));

            m_mesh.AddVertexCoord(leftSide[0]);
            m_mesh.AddVertexCoord(rightSide[0]);
            m_mesh.AddVertexCoord(rightSide[1]);

            m_mesh.AddNormalCoord(glm::normalize(leftSide[0]));
            m_mesh.AddNormalCoord(glm::normalize(rightSide[0]));
            m_mesh.AddNormalCoord(glm::normalize(rightSide[1]));

            //-------------- Bottom half -----------
            leftSide[0].y = -leftSide[0].y;
            leftSide[1].y = -leftSide[1].y;

            rightSide[0].y = -rightSide[0].y;
            rightSide[1].y = -rightSide[1].y;

            m_mesh.AddVertexCoord(rightSide[1]);
            m_mesh.AddVertexCoord(leftSide[0]);
            m_mesh.AddVertexCoord(leftSide[1]);

            m_mesh.AddNormalCoord(glm::normalize(rightSide[1]));
            m_mesh.AddNormalCoord(glm::normalize(leftSide[0]));
            m_mesh.AddNormalCoord(glm::normalize(leftSide[1]));

            m_mesh.AddVertexCoord(leftSide[0]);
            m_mesh.AddVertexCoord(rightSide[1]);
            m_mesh.AddVertexCoord(rightSide[0]);

            m_mesh.AddNormalCoord(glm::normalize(leftSide[0]));
            m_mesh.AddNormalCoord(glm::normalize(rightSide[1]));
            m_mesh.AddNormalCoord(glm::normalize(rightSide[0]));
        }
    }

    m_mesh.SetMode(CMesh::eTriangles);
}

CSphere::CSphere() :
    m_longSubdiv(10),
    m_latSubdiv(10),
    m_radius(1.0) {

    initGeometry();

    m_material.SetShaderProgram("phong");
}

void CSphere::SetRadius(double val_) {
    if (val_ > 0 && !Equal<double>(val_, m_radius)) {
        m_radius = val_;
        initGeometry();
    }
}

double CSphere::GetRadius() const {
    return m_radius;
}

void CSphere::SetUSubdiv(uint val_) {
    if (val_ > 0 && (val_ != m_longSubdiv)) {
        m_longSubdiv = val_;
        initGeometry();
    }
}

uint CSphere::GetUSubdiv() const {
    return m_longSubdiv;
}

void CSphere::SetVSubdiv(uint val_) {
    if (val_ > 0 && (val_ != m_latSubdiv)) {
        m_latSubdiv = val_;
        initGeometry();
    }
}

uint CSphere::GetVSubdiv() const {
    return m_latSubdiv;
}

CMaterial* CSphere::GetMaterial() {
    return &m_material;
}
