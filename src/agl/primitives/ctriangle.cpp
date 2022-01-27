#include "basemath.h"

#include "ctriangle.h"

using namespace agl;

CTriangle::CTriangle() {

    m_mesh.AddVertexCoord(aVec3(-0.5, -0.5, 0.0));
    m_mesh.AddVertexCoord(aVec3( 0.5, -0.5, 0.0));
    m_mesh.AddVertexCoord(aVec3( 0.0,  0.5, 0.0));

    m_mesh.SetMode(CMesh::eTriangles);

    m_material.SetShaderProgram("phong");
}

void CTriangle::UpdateNormals() {
    m_mesh.UpdateNormals();
}

void CTriangle::SetPosition(const aVec3& P0, const aVec3& P1, const aVec3& P2) {
    CMesh::SGdata& data = const_cast<CMesh::SGdata&>(m_mesh.GetData());
    data.vertexBuffer.SetElement(0, P0);
    data.vertexBuffer.SetElement(1, P1);
    data.vertexBuffer.SetElement(2, P2);
}

CMaterial* CTriangle::GetMaterial() {
    return &m_material;
}
