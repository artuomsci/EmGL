#ifdef _WEB
#include <GLES3/gl3.h>
#endif

#include "crenderable.h"
#include "cbase.h"
#include "cshader.h"
#include "clogger.h"
#include "ccamera.h"

using namespace agl;

//---------------------------------------------------------------
CRenderable::CRenderable() :
    m_bVisible(true) {
    }

//---------------------------------------------------------------
CRenderable::~CRenderable() {
    }

//---------------------------------------------------------------
void CRenderable::SetVisible(bool state_) {
    m_bVisible = state_;
    }

//---------------------------------------------------------------
bool CRenderable::IsVisible() const {
    return m_bVisible;
    }

//---------------------------------------------------------------
CMaterial& CRenderable::GetMaterial() {
    return m_material;
    }

//---------------------------------------------------------------
void CRenderable::Render() {

    if (!m_bVisible)
        return;

    SPtr<CShader> ptrShader = CBase::GetBase()->GetShader();
    if (!ptrShader)
        return;

    TShaderProgram              shaderProgram   = m_material.GetShaderProgram();
    const TShaderPropsLocation& properties      = ptrShader->GetProperties(shaderProgram);
    const TShaderPropsData&     propertiesData  = m_material.GetProperties();

    glUseProgram(shaderProgram);

    for (auto pit = properties.begin(); pit != properties.end(); ++pit) {

        TShaderPropId               propId  = pit->first;
        const SUniformsLocation&    prop    = pit->second;

        TShaderPropsData::const_iterator data = propertiesData.find(propId);

        switch (prop.type)
        {
            case e1f:
                glUniform1f(prop.location, data->second.f1);
            break;

            case e2f:
                glUniform2f(prop.location, data->second.v2.x, data->second.v2.y);
            break;

            case e3f:
                glUniform3f(prop.location, data->second.v3.x, data->second.v3.y, data->second.v3.z);
            break;

            case e1i:
                glUniform1i(prop.location, data->second.i1);
            break;

            case e2i:
                glUniform2i(prop.location, (int)data->second.v2.x, (int)data->second.v2.y);
            break;

            case e3i:
                glUniform3i(prop.location, (int)data->second.v3.x, (int)data->second.v3.y, (int)data->second.v3.z);
            break;

            case e4fv: {
            SPtr<CCamera> ptrCamera = CBase::GetBase()->GetCamera();

            if (propId == eProjectionMatr) {
                glUniformMatrix4fv(prop.location, 1, GL_FALSE, &ptrCamera->GetProjectionMat()[0][0]);
                break;
            }

            if (propId == eModelViewMatr) {
                glUniformMatrix4fv(prop.location, 1, GL_FALSE, &ptrCamera->GetModelViewMat()[0][0]);
                break;
            }

            if (propId == eModNormalMatr) {
                glUniformMatrix4fv(prop.location, 1, GL_FALSE, &ptrCamera->GetModNormalMat()[0][0]);
                break;
            }
        }
        break;
        }
    }

//        if (m_material.IsTextured()) {
//            glEnable(GL_TEXTURE_2D);
//            glUniform1i(m_ptrBase->GetShader()->m_uHnd.uptrTex1, 0);
//            glActiveTexture(GL_TEXTURE0);
//            glBindTexture(GL_TEXTURE_2D, m_material.GetTextureID(eDiffuseTex));
//            }


        switch (m_mesh.GetMode())
        {
            case CMesh::ePoints:
            {
                const CMesh::SGdata& mesh = m_mesh.GetData();

                GLuint vVBO = mesh.vertexBuffer.GetId();
                glEnableVertexAttribArray(eVertCoord);
                glBindBuffer(GL_ARRAY_BUFFER, vVBO);
                glVertexAttribPointer(eVertCoord, 3, GL_FLOAT, GL_FALSE, 0, NULL);

                glDrawArrays(GL_POINTS, 0, mesh.vertexBuffer.GetNumElements());

                glDisableVertexAttribArray(eVertCoord);
                glBindBuffer(GL_ARRAY_BUFFER, NULL);
            }
            break;

            case CMesh::eLines:
            {
                const CMesh::SGdata& mesh = m_mesh.GetData();

                glLineWidth(m_mesh.GetLineWidth());

                GLuint vVBO = mesh.vertexBuffer.GetId();
                glEnableVertexAttribArray(eVertCoord);
                glBindBuffer(GL_ARRAY_BUFFER, vVBO);
                glVertexAttribPointer(eVertCoord, 3, GL_FLOAT, GL_FALSE, 0, NULL);

                glDrawArrays(GL_LINES, 0, mesh.vertexBuffer.GetNumElements());

                glDisableVertexAttribArray(eVertCoord);
                glBindBuffer(GL_ARRAY_BUFFER, NULL);
            }
            break;

            case CMesh::eTriangles:
            {
                const CMesh::SGdata& mesh = m_mesh.GetData();

                GLuint vVBO = mesh.vertexBuffer.GetId();
                glEnableVertexAttribArray(eVertCoord);
                glBindBuffer(GL_ARRAY_BUFFER, vVBO);
                glVertexAttribPointer(eVertCoord, 3, GL_FLOAT, GL_FALSE, 0, NULL);

                GLuint nVBO = mesh.normalBuffer.GetId();
                glEnableVertexAttribArray(eVertNorm);
                glBindBuffer(GL_ARRAY_BUFFER, nVBO);
                glVertexAttribPointer(eVertNorm, 3, GL_FLOAT, GL_FALSE, 0, NULL);

                GLuint brcVBO = mesh.barycentBuffer.GetId();
                glEnableVertexAttribArray(eVertBaryCoord);
                glBindBuffer(GL_ARRAY_BUFFER, brcVBO);
                glVertexAttribPointer(eVertBaryCoord, 3, GL_FLOAT, GL_FALSE, 0, NULL);

//                GLuint tVBO = m_gdata.textureBuffer.GetId();
//                glEnableVertexAttribArray(CShader::eVertTexCoord);
//                glBindBuffer(GL_ARRAY_BUFFER, tVBO);
//                glVertexAttribPointer(CShader::eVertTexCoord, 2, GL_FLOAT, GL_FALSE, 0, NULL);

                GLuint iVBO = mesh.indBuffer.GetId();
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iVBO);

                glDrawElements(GL_TRIANGLES, mesh.indBuffer.GetNumElements(), GL_UNSIGNED_INT, (void*)0);

                glDisableVertexAttribArray(eVertCoord);
                glDisableVertexAttribArray(eVertNorm);
                glDisableVertexAttribArray(eVertTexCoord);
                glDisableVertexAttribArray(eVertBaryCoord);

                glBindBuffer(GL_ARRAY_BUFFER, NULL);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
            }
            break;
        }
    }
