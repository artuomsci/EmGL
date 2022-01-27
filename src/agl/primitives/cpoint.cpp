#include "cpoint.h"

using namespace agl;

CPoint::CPoint() :
    m_pntSize(1) {

    m_mesh.AddVertexCoord(aVec3(0, 0, 0));

    m_mesh.SetMode(CMesh::ePoints);

    m_material.SetShaderProgram("primitive");
}

CPoint::CPoint(const aVec3& vec_) : CPoint() {
    this->SetPosition(vec_);
}

float CPoint::GetSize() const {
    return m_pntSize;
}

void CPoint::SetPosition(const aVec3& vec_) {
    CMesh::SGdata& data = const_cast<CMesh::SGdata&>(m_mesh.GetData());
    data.vertexBuffer.SetElement(0, vec_);
}

void CPoint::GetPosition(aVec3& vec_) const {
    m_mesh.GetData().vertexBuffer.GetElement(0, vec_);
}

void CPoint::SetSize(float size_) {
    m_pntSize = size_;
}

CMaterial* CPoint::GetMaterial() {
    return &m_material;
}
