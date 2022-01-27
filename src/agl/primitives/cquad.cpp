#include "rotate_vector.hpp"

#include "basemath.h"

#include "cquad.h"

using namespace agl;
using namespace bu;

const std::vector<aVec3> CQuad::svArr {
        aVec3(-1.0, 0.0, 1.0),
        aVec3(-1.0, 0.0,-1.0),
        aVec3( 1.0, 0.0,-1.0),

        aVec3( 1.0, 0.0,-1.0),
        aVec3( 1.0, 0.0, 1.0),
        aVec3(-1.0, 0.0, 1.0)
        };

void CQuad::initGeometry() {
    m_mesh.Clear();

    std::vector<aVec3> vArr;
    vArr.resize(6);
    for (int i = 0; i < vArr.size(); ++i) {
        vArr[i].x = svArr[i].x * m_width;
        vArr[i].y = 0.0;
        vArr[i].z = svArr[i].z * m_height;
    }

    for (int i = 0; i < vArr.size(); ++i)
        m_mesh.AddVertexCoord(vArr[i]);

    m_mesh.SetMode(CMesh::eTriangles);
}

CQuad::CQuad() :
    m_width(1.0),
    m_height(1.0),
    m_subdiv(4) {

    initGeometry();

    m_material.SetShaderProgram("phong");
    }

void CQuad::UpdateNormals() {
    m_mesh.UpdateNormals();
}

void CQuad::SetWidth(double val_) {
    if (val_ > 0 && !Equal<double>(val_, m_width)) {
        m_width = val_;
        initGeometry();
        }
    }

double CQuad::GetWidth() const {
    return m_width;
    }

void CQuad::SetHeight(double val_) {
    if (val_ > 0 && !Equal<double>(val_, m_height)) {
        m_height = val_;
        initGeometry();
        }
    }

double CQuad::GetHeight() const {
    return m_height;
    }

void CQuad::SetSubdivision(double val_) {
    m_subdiv = val_;
    }

double CQuad::GetSubdivision() const {
    return m_subdiv;
    }

CMaterial* CQuad::GetMaterial() {
    return &m_material;
    }
