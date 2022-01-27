#include "ccamera.h"
#include "cbase.h"
#include "ctransform.h"
#include "../misc/basemath.h"
#include "cwndmanager.h"

using namespace agl;
using namespace bu;

//---------------------------------------------------------------
CCamera::CCamera() :
        m_type      (ePerspective)
    ,   m_leftBr    (-1.0)
    ,   m_rightBr   (1.0)
    ,   m_topBr     (1.0)
    ,   m_bottomBr  (-1.0)
    ,   m_nearBr    (-1.0)
    ,   m_farBr     (1.0)
    ,   m_nearPlane (0.1)
    ,   m_farPlane  (100.0)
    ,   m_fov       (45.0) {

    m_ptrMemCamera = std::make_shared<CMemCamera>(this);
    }

//---------------------------------------------------------------
CCamera::~CCamera() {

}

//---------------------------------------------------------------
void CCamera::Update() {
    switch (m_type) {
        case ePerspective: {
        uint w, h; CBase::GetBase()->GetWndManager()->GetResolution(w, h);
        CBase::GetBase()->GetTransform()->Perspective(m_fov, (double)w / h, m_nearPlane, m_farPlane);
            }
            break;

        case eOrtho: {
        CBase::GetBase()->GetTransform()->Ortho(m_leftBr, m_rightBr, m_bottomBr, m_topBr, m_nearBr, m_farBr);
            }
            break;
        }

    }

//---------------------------------------------------------------
SPtr<IMemento> CCamera::GetMemento() {
    return m_ptrMemCamera;
}

//---------------------------------------------------------------
void CCamera::SetProjectionType(const eCAMTYPE type_) {
    if (type_ == m_type)
        return;

    m_type = type_;
    Update();
    }

//---------------------------------------------------------------
eCAMTYPE CCamera::GetProjectionType() const {
    return m_type;
    }

//---------------------------------------------------------------
void CCamera::IdentityTransform() {
    CBase::GetBase()->GetTransform()->LoadIdentity();
}

//---------------------------------------------------------------
void CCamera::SetPosition(const aVec3& vec_) {
    m_node.SetTranslation(vec_);
    }

//---------------------------------------------------------------
void CCamera::GetPosition(aVec3& vec_) const {
    m_node.GetTranslation(vec_);
    }

//---------------------------------------------------------------
void CCamera::SetOrientation(const aQuat& quat_) {
    m_node.SetOrientation(quat_);
    }

//---------------------------------------------------------------
void CCamera::GetOrientation(aQuat& quat_) const {
    m_node.GetOrientation(quat_);
    }

//---------------------------------------------------------------
const aMat4& CCamera::GetModelViewMat() const {
    return CBase::GetBase()->GetTransform()->GetModelViewMat();
    }

//---------------------------------------------------------------
const aMat4& CCamera::GetProjectionMat() const {
    return CBase::GetBase()->GetTransform()->GetProjectionMat();
    }

//---------------------------------------------------------------
const aMat4& CCamera::GetModNormalMat() const {
    return CBase::GetBase()->GetTransform()->GetModNormalMat();
    }

//---------------------------------------------------------------
void CCamera::SetNearPlane(const double in_) {
    if (Equal<double>(m_nearPlane, in_))
        return;

    m_nearPlane = in_;
    uint w, h;
    CBase::GetBase()->GetWndManager()->GetResolution(w, h);
    CBase::GetBase()->GetTransform()->Perspective(m_fov, (double)w / h, m_nearPlane, m_farPlane);
    }

//---------------------------------------------------------------
double CCamera::GetNearPlane() const {
    return m_nearPlane;
    }

//---------------------------------------------------------------
void CCamera::SetFarPlane(const double in_) {
    if (Equal<double>(m_farPlane, in_))
        return;

    m_farPlane = in_;
    uint w, h; CBase::GetBase()->GetWndManager()->GetResolution(w, h);
    CBase::GetBase()->GetTransform()->Perspective(m_fov, (double)w / h, m_nearPlane, m_farPlane);
    }

//---------------------------------------------------------------
double CCamera::GetFarPlane() const {
    return m_farPlane;
    }

//---------------------------------------------------------------
void CCamera::SetFov(const double in_) {
    if (Equal<double>(m_fov, in_))
        return;

    m_fov = in_;
    uint w, h; CBase::GetBase()->GetWndManager()->GetResolution(w, h);
    CBase::GetBase()->GetTransform()->Perspective(m_fov, (double)w / h, m_nearPlane, m_farPlane);
    }

//---------------------------------------------------------------
double CCamera::GetFov() const {
    return m_fov;
    }

//---------------------------------------------------------------
void CCamera::SetViewVolume(double left_, double right_, double bottom_, double top_, double near_, double far_) {
    if (
            Equal<double>(m_leftBr,    left_)      &&
            Equal<double>(m_rightBr,   right_)     &&
            Equal<double>(m_bottomBr,  bottom_)    &&
            Equal<double>(m_topBr,     top_)       &&
            Equal<double>(m_nearBr,    near_)      &&
            Equal<double>(m_farBr,     far_)
            )
        return;

    m_leftBr    = left_;
    m_rightBr   = right_;
    m_bottomBr  = bottom_;
    m_topBr     = top_;
    m_nearBr    = near_;
    m_farBr     = far_;

    CBase::GetBase()->GetTransform()->Ortho(m_leftBr, m_rightBr, m_bottomBr, m_topBr, m_nearBr, m_farBr);
}

//---------------------------------------------------------------
void CCamera::GetViewVolume(double &left_, double &right_, double &bottom_, double &top_, double &near_, double &far_) const {
    left_   = m_leftBr;
    right_  = m_rightBr;
    bottom_ = m_bottomBr;
    top_    = m_topBr;
    near_   = m_nearBr;
    far_    = m_farBr;
    }

//---------------------------------------------------------------
CMemCamera::CMemCamera(CCamera* pCamera_) {
    m_pCamera = pCamera_;
}

//---------------------------------------------------------------
void CMemCamera::PushState() {

    SCamState state;

    aQuat camOrient; m_pCamera->GetOrientation(camOrient);
    state.node.SetOrientation(camOrient);
    aVec3 camPos; m_pCamera->GetPosition(camPos);
    state.node.SetTranslation(camPos);

    state.farPlane  = m_pCamera->GetFarPlane();
    state.nearPlane = m_pCamera->GetNearPlane();
    state.fov       = m_pCamera->GetFov();

    m_pCamera->GetViewVolume(state.leftBr, state.rightBr, state.bottomBr, state.topBr, state.nearBr, state.farBr);

    state.type = m_pCamera->GetProjectionType();

    m_states.push_back(state);
}

//---------------------------------------------------------------
void CMemCamera::PopState() {
    SCamState& state = m_states.back();

    aQuat camOrient; state.node.GetOrientation(camOrient);
    m_pCamera->SetOrientation(camOrient);
    aVec3 camPos; state.node.GetTranslation(camPos);
    m_pCamera->SetPosition(camPos);

    m_pCamera->SetFarPlane(state.farPlane);
    m_pCamera->SetNearPlane(state.nearPlane);
    m_pCamera->SetFov(state.fov);

    m_pCamera->SetViewVolume(state.leftBr, state.rightBr, state.bottomBr, state.topBr, state.nearBr, state.farBr);

    m_pCamera->SetProjectionType(state.type);

    m_states.pop_back();
}
