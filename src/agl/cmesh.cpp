#include "rotate_vector.hpp"

#include "cmesh.h"
#include "cshader.h"

using namespace agl;

//---------------------------------------------------------------
CMesh::CMesh() :
        m_lineWidth (1.0)
    ,   m_mode      (eTriangles) {
}

//---------------------------------------------------------------
void CMesh::Clear() {
    m_data.barycentBuffer.Clear();
    m_data.indBuffer.Clear();
    m_data.normalBuffer.Clear();
    m_data.textureBuffer.Clear();
    m_data.vertexBuffer.Clear();
}

//---------------------------------------------------------------
void CMesh::UpdateNormals() {
    switch (m_mode) {
    case eTriangles: {
        for (int i = 0; i < m_data.indBuffer.GetNumElements() / 3; ++i) {
            uint i0, i1, i2;

            m_data.indBuffer.GetElement(i * 3 + 0, i0);
            m_data.indBuffer.GetElement(i * 3 + 1, i1);
            m_data.indBuffer.GetElement(i * 3 + 2, i2);

            aVec3 v0, v1, v2, n;
            m_data.vertexBuffer.GetElement(i0, v0);
            m_data.vertexBuffer.GetElement(i1, v1);
            m_data.vertexBuffer.GetElement(i2, v2);

            n = glm::cross(v0 - v1, v0 - v2);
            n = glm::normalize(n);

            m_data.normalBuffer.SetElement(i * 3 + 0, n);
            m_data.normalBuffer.SetElement(i * 3 + 1, n);
            m_data.normalBuffer.SetElement(i * 3 + 2, n);
        }
    }
        break;

    default:
        break;
    }
}

//---------------------------------------------------------------
void CMesh::SetMode(eMeshMode mode_) {
    m_mode = mode_;

    switch (mode_) {

    case ePoints: {
        m_data.vertexBuffer.PushData(GL_ARRAY_BUFFER);
    }
        break;

    case eLines: {
        m_data.vertexBuffer.PushData(GL_ARRAY_BUFFER);
    }
        break;

    case eTriangles: {

        if (m_data.indBuffer.GetNumElements() == 0) {
            for (int i = 0; i < m_data.vertexBuffer.GetNumElements(); ++i) {
                m_data.indBuffer.AddElement(i);
            }
        }

        if (m_data.textureBuffer.GetNumElements() == 0) {
            for (int i = 0; i < m_data.vertexBuffer.GetNumElements(); ++i) {
                const static aVec2 tVec0(0.0, 1.0);
                const static aVec2 tVec1(1.0, 0.0);

                m_data.textureBuffer.AddElement(tVec0);
                m_data.textureBuffer.AddElement(tVec1);
            }
        }

        if (m_data.barycentBuffer.GetNumElements() == 0) {
            for (int i = 0; i < m_data.vertexBuffer.GetNumElements(); ++i) {
                const static aVec3 bVec0(1.0, 0.0, 0.0);
                const static aVec3 bVec1(0.0, 1.0, 0.0);
                const static aVec3 bVec2(0.0, 0.0, 1.0);

                m_data.barycentBuffer.AddElement(bVec0);
                m_data.barycentBuffer.AddElement(bVec1);
                m_data.barycentBuffer.AddElement(bVec2);
            }
        }

        if (m_data.normalBuffer.GetNumElements() == 0) {
            for (int i = 0; i < m_data.vertexBuffer.GetNumElements() / 3; ++i) {
                aVec3 v0, v1, v2, n;
                m_data.vertexBuffer.GetElement(i * 3 + 0, v0);
                m_data.vertexBuffer.GetElement(i * 3 + 1, v1);
                m_data.vertexBuffer.GetElement(i * 3 + 2, v2);

                n = glm::cross(v0 - v1, v0 - v2);
                n = glm::normalize(n);

                m_data.normalBuffer.AddElement(n);
                m_data.normalBuffer.AddElement(n);
                m_data.normalBuffer.AddElement(n);
            }
        }

        m_data.normalBuffer.PushData(GL_ARRAY_BUFFER);
        m_data.vertexBuffer.PushData(GL_ARRAY_BUFFER);
        m_data.textureBuffer.PushData(GL_ARRAY_BUFFER);
        m_data.indBuffer.PushData(GL_ELEMENT_ARRAY_BUFFER);
        m_data.barycentBuffer.PushData(GL_ARRAY_BUFFER);
    }
        break;

    default:
        break;
    }
}

//---------------------------------------------------------------
CMesh::eMeshMode CMesh::GetMode() const {
    return m_mode;
}

//---------------------------------------------------------------
void CMesh::AddVertexCoord(const aVec3& vec_) {
    m_data.vertexBuffer.AddElement(vec_);
}

//---------------------------------------------------------------
void CMesh::AddNormalCoord(const aVec3& vec_) {
    m_data.normalBuffer.AddElement(vec_);
}

//---------------------------------------------------------------
void CMesh::AddBarycentricCoord(const aVec3& vec_) {
    m_data.barycentBuffer.AddElement(vec_);
}

//---------------------------------------------------------------
void CMesh::AddIndex(uint ind_) {
    m_data.indBuffer.AddElement(ind_);
}

//---------------------------------------------------------------
void CMesh::AddTextureCoord(const aVec2& vec_) {
    m_data.textureBuffer.AddElement(vec_);
}

//---------------------------------------------------------------
const CMesh::SGdata& CMesh::GetData() const {
    return m_data;
}

//---------------------------------------------------------------
void CMesh::SetLineWidth(float val_) {
    m_lineWidth = val_;
}

//---------------------------------------------------------------
float CMesh::GetLineWidth() const {
    return m_lineWidth;
}
