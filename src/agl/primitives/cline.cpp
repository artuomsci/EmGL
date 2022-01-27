#include "basemath.h"
#include "cline.h"

using namespace agl;
using namespace bu;

CLine::CLine() :
    m_length(1.0) {

    m_mesh.AddVertexCoord(aVec3(0.0, 0.0, 0.0));
    m_mesh.AddVertexCoord(aVec3(0.0, m_length, 0.0));

    m_mesh.SetMode(CMesh::eLines);

    m_material.SetShaderProgram("primitive");
    }

CLine::CLine(const aVec3& p0_, const aVec3& p1_) : CLine() {
    this->SetPosition(p0_, p1_);
}

void CLine::SetPosition(const aVec3& p0_, const aVec3& p1_) {
    CMesh::SGdata& data = const_cast<CMesh::SGdata&>(m_mesh.GetData());
    data.vertexBuffer.SetElement(0, p0_);
    data.vertexBuffer.SetElement(1, p1_);
}

void CLine::GetPosition(aVec3& p0_, aVec3& p1_) const {
    const CMesh::SGdata& data = m_mesh.GetData();
    data.vertexBuffer.GetElement(0, p0_);
    data.vertexBuffer.GetElement(1, p1_);
}

void CLine::SetLength(double val_) {
    if (!Equal<double>(val_, 0.0) && !Equal<double>(val_, m_length)) {
        m_length = val_;
        CMesh::SGdata& data = const_cast<CMesh::SGdata&>(m_mesh.GetData());
        aVec3 P0, P1, P2;
        data.vertexBuffer.GetElement(0, P0);
        data.vertexBuffer.GetElement(1, P1);
        P2 = glm::normalize(P1 - P0) * (float)val_;
        data.vertexBuffer.SetElement(1, P0 + P2);
    }
}

double CLine::GetLength() const {
    return m_length;
}

void CLine::SetWidth(float width_) {
    m_mesh.SetLineWidth(width_);
}

float CLine::GetWidth() const {
    return m_mesh.GetLineWidth();
}

CMaterial* CLine::GetMaterial() {
    return &m_material;
}
