#include "crectangle.h"

using namespace agl;

CRectangle::CRectangle() {
    initGeometry();

    m_material.SetShaderProgram("diffuse");
}

void CRectangle::initGeometry() {
    m_mesh.Clear();

    double x0, y0, x1, y1;
    m_rect.Get(x0, y0, x1, y1);

    m_mesh.AddVertexCoord(aVec3(x0, y0, 0));
    m_mesh.AddVertexCoord(aVec3(x1, y0, 0));

    m_mesh.AddVertexCoord(aVec3(x1, y0, 0));
    m_mesh.AddVertexCoord(aVec3(x1, y1, 0));

    m_mesh.AddVertexCoord(aVec3(x1, y1, 0));
    m_mesh.AddVertexCoord(aVec3(x0, y1, 0));

    m_mesh.AddVertexCoord(aVec3(x0, y1, 0));
    m_mesh.AddVertexCoord(aVec3(x0, y0, 0));

    m_mesh.SetMode(CMesh::eMeshMode::eLines);
}

double CRectangle::GetWidth() const {
    return m_rect.GetWidth();
}

double CRectangle::GetHeight() const {
    return m_rect.GetHeight();
}

void CRectangle::Get(double& x0_, double& y0_, double& x1_, double& y1_) const {
    m_rect.Get(x0_, y0_, x1_, y1_);
}

void CRectangle::Set(double x0_, double y0_, double x1_, double y1_) {
    m_rect.Set(x0_, y0_, x1_, y1_);
    initGeometry();
}

void CRectangle::Set_P0(double x0_, double y0_) {
    m_rect.Set_P0(x0_, y0_);
    initGeometry();
}

void CRectangle::Set_P1(double x1_, double y1_) {
    m_rect.Set_P1(x1_, y1_);
    initGeometry();
}

CMaterial* CRectangle::GetMaterial() {
    return &m_material;
}
