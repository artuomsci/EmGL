#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "ctransform.h"
#include "basemath.h"

using namespace agl;
using namespace bu;

//---------------------------------------------------------------
CTransform::CTransform() :
        m_matIndex      (0)
      , m_ProjectionMat (aMat4(0.0f))
      , m_NodeMat       (1.0f) {
    }

//---------------------------------------------------------------
CTransform::~CTransform() {

}

//---------------------------------------------------------------
void CTransform::Translate(double x_, double y_, double z_) {
    m_ModelViewMat[m_matIndex] = glm::translate(aVec3(x_, y_, z_)) * m_ModelViewMat[m_matIndex];
    }

//---------------------------------------------------------------
void CTransform::Translate(const aVec3& vec_) {
    m_ModelViewMat[m_matIndex] = glm::translate(vec_) * m_ModelViewMat[m_matIndex];
}

//---------------------------------------------------------------
void CTransform::Rotate(double ane_, double x_, double y_, double z_) {
    m_ModelViewMat[m_matIndex] = m_ModelViewMat[m_matIndex] * glm::rotate((float)ane_, aVec3(x_, y_, z_));
    }

//---------------------------------------------------------------
void CTransform::Rotate(const aQuat &orientation_) {
    aMat4 rotMat = glm::mat4_cast(orientation_);
    m_ModelViewMat[m_matIndex] = m_ModelViewMat[m_matIndex] * rotMat;
    }

//---------------------------------------------------------------
void CTransform::Scale(double x_, double y_, double z_) {
    m_ModelViewMat[m_matIndex] = glm::scale(aVec3(x_, y_, z_)) * m_ModelViewMat[m_matIndex];
    }

//---------------------------------------------------------------
void CTransform::LoadIdentity() {
    m_ModelViewMat[m_matIndex] = aMat4(1.0f);
    m_NodeMat = aMat4(1.0f);
    }

//---------------------------------------------------------------
void CTransform::LookAt(aVec3 eyePos_, aVec3 viewPoint_, aVec3 up_) {
    m_ModelViewMat[m_matIndex] = glm::lookAt(eyePos_, viewPoint_, up_);
    }

//---------------------------------------------------------------
void CTransform::Perspective(double fov_, double WndRatio_, double nearplane_, double farplane_) {
    m_ProjectionMat = glm::perspective((float)fov_ * FDEG2RAD, (float)WndRatio_, (float)nearplane_, (float)farplane_);
    }

//---------------------------------------------------------------
void CTransform::Ortho(double left_, double right_,
                       double bottom_, double top_,
                       double nearplane_, double farplane_) {
    m_ProjectionMat = glm::ortho((float)left_, (float)right_, (float)bottom_, (float)top_, (float)nearplane_, (float)farplane_);
    }

//---------------------------------------------------------------
void CTransform::PushMatrix() {
    if (m_matIndex < MATRIXSTACKSIZE - 1) {
        ++m_matIndex;
        m_ModelViewMat[m_matIndex] = m_ModelViewMat[m_matIndex - 1];
        }
    }

//---------------------------------------------------------------
void CTransform::PopMatrix() {
    if (m_matIndex > 0)
        --m_matIndex;
    }

//---------------------------------------------------------------
int CTransform::GetMatInd() const {
    return(m_matIndex);
    }

//---------------------------------------------------------------
void CTransform::SetNodeTransform(const aVec3 &pos_, const aVec3 &rot_, bool ismovable_) {
    if (ismovable_)
        m_NodeMat = glm::translate(pos_) *
                    glm::rotate(rot_.x, aVec3(1.0f, 0.0f, 0.0f)) *
                    glm::rotate(rot_.y, aVec3(0.0f, 1.0f, 0.0f)) *
                    glm::rotate(rot_.z, aVec3(0.0f, 0.0f, 1.0f));
    else
        m_NodeMat = aMat4(1.0f);
    }

//---------------------------------------------------------------
void CTransform::SetNodeTransform(const aVec3 &pos_, const aQuat& quat_, bool ismovable_) {
    aMat4 rotMat = glm::mat4_cast(quat_);
    if (ismovable_)
        m_NodeMat = glm::translate(pos_) * rotMat;
    else
        m_NodeMat = aMat4(1.0f);
    }

//---------------------------------------------------------------
aMat4 &CTransform::GetModelViewMat() {
    m_ModelViewMatTemp = m_ModelViewMat[m_matIndex] * m_NodeMat;
    return m_ModelViewMatTemp;
    }

//---------------------------------------------------------------
aMat4 &CTransform::GetProjectionMat() {
    return m_ProjectionMat;
    }

//---------------------------------------------------------------
aMat4 &CTransform::GetModNormalMat() {
    m_ModNormalMatTemp = glm::transpose(glm::inverse(m_ModelViewMat[m_matIndex] * m_NodeMat));
    return m_ModNormalMatTemp;
    }

//---------------------------------------------------------------
void CTransform::IntoScreenCoord(const aVec3 &worldVec_, aVec2 &scrVec_) {
    // Setting pipeline transformation matrix
    aMat4 trMat = GetProjectionMat() * GetModelViewMat();
    // Transforming point to viewport coordinates
    aVec4 newPnt = trMat * aVec4(worldVec_, 1.0f);
    scrVec_.x = newPnt.x / newPnt.w;
    scrVec_.y = newPnt.y / newPnt.w;
    }
