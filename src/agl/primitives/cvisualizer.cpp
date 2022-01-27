#include "cvisualizer.h"

using namespace agl;

CVisualizer::CVisualizer() {
    m_material.SetShaderProgram("primitive");
}

void CVisualizer::Update(CRenderable* renderable_, float scale_) {
    const CMesh::SGdata& data = renderable_->m_mesh.GetData();

    m_mesh.Clear();

    for (uint i = 0; i < data.indBuffer.GetNumElements(); ++i) {
        uint ind;
        data.indBuffer.GetElement(i, ind);

        aVec3 pnt, n;
        data.vertexBuffer.GetElement(ind, pnt);
        data.normalBuffer.GetElement(ind, n);

        m_mesh.AddVertexCoord(pnt);
        m_mesh.AddVertexCoord(pnt + n * scale_);
    }

    m_mesh.SetMode(CMesh::eLines);

    m_material.SetShaderProgram("primitive");
}

CMaterial* CVisualizer::GetMaterial() {
    return &m_material;
    }
