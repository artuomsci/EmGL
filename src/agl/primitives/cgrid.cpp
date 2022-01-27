#include "basemath.h"

#include "cgrid.h"

using namespace agl;
using namespace bu;

void CGrid::initGeometry() {
    m_mesh.Clear();

    // Base vertices
    aVec3 uLeftTopCorner(-0.5, 0.0, 0.5);
    aVec3 uLeftBottomCorner(-0.5, 0.0, -0.5);

    aVec3 vLeftTopCorner(-0.5, 0.0, 0.5);
    aVec3 vRightTopCorner(0.5, 0.0, 0.5);

    // Columns step
    double uStep = 1.0 / m_uSubdiv;
    // Rows step
    double vStep = 1.0 / m_vSubdiv;

    std::vector<aVec3> vArr;

    // Filling up columns
    for (int i = 0; i < m_uSubdiv + 1; ++i) {
        vArr.push_back(aVec3(uLeftTopCorner.x + uStep * i, uLeftTopCorner.y, uLeftTopCorner.z));
        vArr.push_back(aVec3(uLeftBottomCorner.x + uStep * i, uLeftBottomCorner.y, uLeftBottomCorner.z));
    }

    // Filling up rows
    for (int i = 0; i < m_vSubdiv + 1; ++i) {
        vArr.push_back(aVec3(vLeftTopCorner.x, vLeftTopCorner.y, vLeftTopCorner.z - vStep * i));
        vArr.push_back(aVec3(vRightTopCorner.x, vRightTopCorner.y, vRightTopCorner.z - vStep * i));
    }

    // Scaling
    for (int i = 0; i < vArr.size(); ++i) {
        vArr[i] = aVec3(vArr[i].x * m_width, vArr[i].y, vArr[i].z);
        vArr[i] = aVec3(vArr[i].x, vArr[i].y, vArr[i].z * m_height);
    }

    for (int i = 0; i < vArr.size(); ++i)
        m_mesh.AddVertexCoord(vArr[i]);

    m_mesh.SetMode(CMesh::eLines);
}

CGrid::CGrid() :
    m_width(1.0),
    m_height(1.0),
    m_uSubdiv(2),
    m_vSubdiv(2) {

    initGeometry();

    m_material.SetShaderProgram("primitive");
    }

void CGrid::SetWidth(double val_) {
    if (val_ > 0 && !Equal<double>(val_, m_width)) {
        m_width = val_;
        initGeometry();
        }
    }

double CGrid::GetWidth() const {
    return m_width;
    }

void CGrid::SetHeight(double val_) {
    if (val_ > 0 && !Equal<double>(val_, m_height)) {
        m_height = val_;
        initGeometry();
        }
    }

double CGrid::GetHeight() const {
    return m_height;
    }

void CGrid::SetUSubdiv(uint val_) {
    if (val_ > 0 && (val_ != m_uSubdiv)) {
        m_uSubdiv = val_;
        initGeometry();
        }
    }

void CGrid::SetVSubdiv(uint val_) {
    if (val_ > 0 && (val_ != m_vSubdiv)) {
        m_vSubdiv = val_;
        initGeometry();
        }
    }

uint CGrid::GetUSubdiv() const {
    return m_uSubdiv;
    }

uint CGrid::GetVSubdiv() const {
    return m_vSubdiv;
    }

CMaterial* CGrid::GetMaterial() {
    return &m_material;
    }
