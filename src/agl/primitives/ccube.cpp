#include <vector>

#include "basemath.h"

#include "ccube.h"

using namespace agl;
using namespace bu;

const std::vector<aVec3> CCube::svArr {
        /**< Front face */
        aVec3(-1.0, 1.0, 1.0),
        aVec3( 1.0, 1.0, 1.0),
        aVec3( 1.0,-1.0, 1.0),
        aVec3(-1.0,-1.0, 1.0),
        /**< Back face */
        aVec3(-1.0, 1.0,-1.0),
        aVec3( 1.0, 1.0,-1.0),
        aVec3( 1.0,-1.0,-1.0),
        aVec3(-1.0,-1.0,-1.0),
        /**< Top face */
        aVec3(-1.0, 1.0, 1.0),
        aVec3(-1.0, 1.0,-1.0),
        aVec3( 1.0, 1.0,-1.0),
        aVec3( 1.0, 1.0, 1.0),
        /**< Bottom face */
        aVec3(-1.0,-1.0, 1.0),
        aVec3(-1.0,-1.0,-1.0),
        aVec3( 1.0,-1.0,-1.0),
        aVec3( 1.0,-1.0, 1.0),
        /**< Left face */
        aVec3(-1.0, 1.0, 1.0),
        aVec3(-1.0, 1.0,-1.0),
        aVec3(-1.0,-1.0,-1.0),
        aVec3(-1.0,-1.0, 1.0),
        /**< Right face */
        aVec3( 1.0, 1.0, 1.0),
        aVec3( 1.0, 1.0,-1.0),
        aVec3( 1.0,-1.0,-1.0),
        aVec3( 1.0,-1.0, 1.0)
        };

const std::vector<aVec3> CCube::snArr {
        /**< Front face */
        aVec3( 0.0, 0.0, 1.0),
        aVec3( 0.0, 0.0, 1.0),
        aVec3( 0.0, 0.0, 1.0),
        aVec3( 0.0, 0.0, 1.0),
        /**< Back face */
        aVec3( 0.0, 0.0,-1.0),
        aVec3( 0.0, 0.0,-1.0),
        aVec3( 0.0, 0.0,-1.0),
        aVec3( 0.0, 0.0,-1.0),
        /**< Top face */
        aVec3( 0.0, 1.0, 0.0),
        aVec3( 0.0, 1.0, 0.0),
        aVec3( 0.0, 1.0, 0.0),
        aVec3( 0.0, 1.0, 0.0),
        /**< Bottom face */
        aVec3( 0.0,-1.0, 0.0),
        aVec3( 0.0,-1.0, 0.0),
        aVec3( 0.0,-1.0, 0.0),
        aVec3( 0.0,-1.0, 0.0),
        /**< Left face */
        aVec3(-1.0, 0.0, 0.0),
        aVec3(-1.0, 0.0, 0.0),
        aVec3(-1.0, 0.0, 0.0),
        aVec3(-1.0, 0.0, 0.0),
        /**< Right face */
        aVec3( 1.0, 0.0, 0.0),
        aVec3( 1.0, 0.0, 0.0),
        aVec3( 1.0, 0.0, 0.0),
        aVec3( 1.0, 0.0, 0.0)
        };

const std::vector<aVec3> CCube::sbArr {
        /**< Front face */
        aVec3( 1.0, 0.0, 0.0),
        aVec3( 0.0, 1.0, 0.0),
        aVec3( 0.0, 0.0, 1.0),
        aVec3( 0.0, 1.0, 0.0),
        /**< Back face */
        aVec3( 1.0, 0.0, 0.0),
        aVec3( 0.0, 1.0, 0.0),
        aVec3( 0.0, 0.0, 1.0),
        aVec3( 0.0, 1.0, 0.0),
        /**< Top face */
        aVec3( 0.0, 0.0, 1.0),
        aVec3( 0.0, 1.0, 0.0),
        aVec3( 0.0, 0.0, 1.0),
        aVec3( 1.0, 0.0, 0.0),
        /**< Bottom face */
        aVec3( 0.0, 0.0, 1.0),
        aVec3( 0.0, 1.0, 0.0),
        aVec3( 0.0, 0.0, 1.0),
        aVec3( 1.0, 0.0, 0.0),
        /**< Left face */
        aVec3( 1.0, 0.0, 0.0),
        aVec3( 0.0, 1.0, 0.0),
        aVec3( 0.0, 0.0, 1.0),
        aVec3( 0.0, 1.0, 0.0),
        /**< Right face */
        aVec3( 1.0, 0.0, 0.0),
        aVec3( 0.0, 1.0, 0.0),
        aVec3( 0.0, 0.0, 1.0),
        aVec3( 0.0, 1.0, 0.0)
        };

const std::vector<uint> CCube::siArr {
        /**< Front face */
        2, 1, 0,
        3, 2, 0,
        /**< Back face */
        5, 6, 4,
        6, 7, 4,
        /**< Top face */
        9, 8, 11,
        11, 10, 9,
        /**< Bottom face */
        15, 12, 13,
        14, 15, 13,
        /**< Left face */
        16, 17, 18,
        19, 16, 18,
        /**< Right face */
        22, 21, 20,
        23, 22, 20
    };

void CCube::initGeometry() {
    m_mesh.Clear();

    std::vector<aVec3> vArr;
    vArr.resize(24);
    for (int i = 0; i < vArr.size(); ++i) {
        vArr[i].x = svArr[i].x * m_width;
        vArr[i].y = svArr[i].y * m_height;
        vArr[i].z = svArr[i].z * m_length;
    }

    for (int i = 0; i < vArr.size(); ++i)
        m_mesh.AddVertexCoord(vArr[i]);

    for (int i = 0; i < siArr.size(); ++i)
        m_mesh.AddIndex(siArr[i]);

    for (int i = 0; i < snArr.size(); ++i)
        m_mesh.AddNormalCoord(snArr[i]);

    for (int i = 0; i < sbArr.size(); ++i)
        m_mesh.AddBarycentricCoord(sbArr[i]);

    m_mesh.SetMode(CMesh::eTriangles);
    }

CCube::CCube() :
    m_width(1.0f),
    m_height(1.0f),
    m_length(1.0f) {

    initGeometry();

    m_material.SetShaderProgram("phong");
    }

void CCube::SetWidth(double val_) {
    if (val_ > 0 && !Equal<double>(val_, m_width)) {
        m_width = val_;
        initGeometry();
        }
    }

double CCube::GetWidth() const {
    return m_width;
    }

void CCube::SetHeight(double val_) {
    if (val_ > 0 && !Equal<double>(val_, m_height)) {
        m_height = val_;
        initGeometry();
        }
    }

double CCube::GetHeight() const {
    return m_height;
    }

void CCube::SetLength(double val_) {
    if (val_ > 0 && !Equal<double>(val_, m_length)) {
        m_length = val_;
        initGeometry();
        }
    }

double CCube::GetLength() const {
    return m_length;
    }

CMaterial* CCube::GetMaterial() {
    return &m_material;
    }
