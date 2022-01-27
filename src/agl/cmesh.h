#ifndef CMESH_H
#define CMESH_H

#include "basicdefs.h"
#include "cbuffer.hpp"

namespace agl {

class CMesh
{
public:

    /**< Geometry VBO data */
    struct SGdata {
        CBuffer<aVec3>  normalBuffer;
        CBuffer<aVec3>  vertexBuffer;
        CBuffer<aVec2>  textureBuffer;
        CBuffer<aVec3>  barycentBuffer;
        CBuffer<uint>   indBuffer;
        GLuint          vao;
        SGdata() : vao(0) {}
        };

    enum eMeshMode { eTriangles, eLines, ePoints };

    CMesh();
    void            Clear();
    void            UpdateNormals();
    void            SetMode(eMeshMode mode_);
    eMeshMode       GetMode() const;
    void            AddVertexCoord(const aVec3& vec_);
    void            AddBarycentricCoord(const aVec3& vec_);
    void            AddNormalCoord(const aVec3& vec_);
    void            AddIndex(uint ind_);
    void            AddTextureCoord(const aVec2& vec_);
    const SGdata&   GetData() const;
    void            SetLineWidth(float val_);
    float           GetLineWidth() const;

private:

    SGdata      m_data;
    eMeshMode   m_mode;
    float       m_lineWidth;
};

}

#endif // CMESH_H
