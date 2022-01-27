#include "cnode.h"
#include "cbase.h"
#include "crenderer.h"
#include "crenderable.h"

#include <algorithm>

using namespace agl;

nodeId CNode::m_idCounter = 1;

//---------------------------------------------------------------
CNode::CNode() :
      m_isMovable   (true)
    , m_isSelected  (false)
    , m_parentId    (0) {

    m_id = m_idCounter++;
    }

//---------------------------------------------------------------
void CNode::SetTranslation(const aVec3& vec_) {
        //m_pos = vec_;
    }

//---------------------------------------------------------------
void CNode::GetTranslation(aVec3& vec_) const {
    if (m_parentId)
        if (const SPtr<CRenderable> ptrRnd = CBase::GetBase()->GetRenderer()->GetRenderable(m_parentId)) {
            aVec3 pos; ptrRnd->GetTranslation(pos);
            aQuat orient; ptrRnd->GetOrientation(orient);
            //vec_ = pos + orient * m_pos;
            return;
        }

    //vec_ = m_pos;
    }

//---------------------------------------------------------------
void CNode::SetOrientation(const aQuat& orientation_) {
        //m_orientation = orientation_;
    }

//---------------------------------------------------------------
void CNode::GetOrientation(aQuat& quat_) const {
    if (m_parentId)
        if (const SPtr<CRenderable> ptrRnd = CBase::GetBase()->GetRenderer()->GetRenderable(m_parentId)) {
            aQuat orient; ptrRnd->GetOrientation(orient);
            //quat_ = orient * m_orientation;
            return;
        }

    //quat_ = m_orientation;
    }

//---------------------------------------------------------------
bool CNode::IsMovable() const {
    return m_isMovable;
    }

//---------------------------------------------------------------
void CNode::SetMovable(bool state_) {
    m_isMovable = state_;
    }

//---------------------------------------------------------------
nodeId CNode::GetId() const {
    return m_id;
    }

//---------------------------------------------------------------
void CNode::SetSelected(bool state_) {
    m_isSelected = state_;
    }

//---------------------------------------------------------------
bool CNode::IsSelected() const {
    return m_isSelected;
    }

//---------------------------------------------------------------
void CNode::SetParent(nodeId id_) {

    if (id_ == 0)
        return;

    const SPtr<CRenderable> ptrRnd = CBase::GetBase()->GetRenderer()->GetRenderable(id_);
    if (!ptrRnd)
        return;

    aQuat quat; ptrRnd->GetTransform(quat, eCOORD_TYPE::eGlobal);
    quat = glm::inverse(quat);
    m_orientationLocal = quat * m_orientationLocal;

    aVec3 vec; ptrRnd->GetTransform(vec, eCOORD_TYPE::eGlobal);
    m_posLocal = quat * m_posGlobal - vec;

    m_parentId = id_;
}

//---------------------------------------------------------------
nodeId CNode::GetParent() const {
    return m_parentId;
}

//---------------------------------------------------------------
bool CNode::HasParent() const {
    return m_parentId == 0 ? false : true;
}

//---------------------------------------------------------------
void CNode::DetachParent() {
    m_parentId = 0;
}

//---------------------------------------------------------------
void CNode::AddChild(nodeId id_) {
    m_children.push_back(id_);
}

//---------------------------------------------------------------
void CNode::RemoveChild(nodeId id_) {
    const auto& it = std::find(m_children.begin(), m_children.end(), id_);
    if (it != m_children.end())
        m_children.erase(it);
}

//---------------------------------------------------------------
bool CNode::HasChildren() const {
    return m_children.size() != 0 ? true : false;
}

//---------------------------------------------------------------
void CNode::Update() {
    if (HasParent()) {
        if (const SPtr<agl::CRenderer> ptrRenderer = CBase::GetBase()->GetRenderer()) {
            if (const SPtr<CRenderable> ptrRnd = ptrRenderer->GetRenderable(m_parentId)) {
                aVec3 vec; ptrRnd->GetTransform(vec, eCOORD_TYPE::eGlobal);
                aQuat quat; ptrRnd->GetTransform(quat, eCOORD_TYPE::eGlobal);
                m_posGlobal = (m_posLocal + vec) * quat;
                m_orientationGlobal = quat * m_orientationLocal;
            }
        }
    }
}

//---------------------------------------------------------------
void CNode::GetTransform(aQuat& quat_, eCOORD_TYPE type_) const {
    ((type_ == eCOORD_TYPE::eLocal) && HasParent()) ? quat_ = m_orientationLocal : quat_ = m_orientationGlobal;
}

//---------------------------------------------------------------
void CNode::SetTransform(const aQuat& quat_) {

    m_orientationGlobal = m_orientationLocal = quat_;

    Update();

    const SPtr<agl::CRenderer> ptrRenderer = CBase::GetBase()->GetRenderer();
    for (auto& it : m_children)
        if (const SPtr<CRenderable> ptrRnd = ptrRenderer->GetRenderable(it))
            ptrRnd->Update();
}

//---------------------------------------------------------------
void CNode::GetTransform(aVec3& vec_, eCOORD_TYPE type_) const {
    ((type_ == eCOORD_TYPE::eLocal) && HasParent()) ? vec_ = m_posLocal : vec_ = m_posGlobal;
}

//---------------------------------------------------------------
void CNode::SetTransform(const aVec3 &vec_) {

    m_posLocal = m_posGlobal = vec_;

    Update();

    const SPtr<agl::CRenderer> ptrRenderer = CBase::GetBase()->GetRenderer();
    for (auto& it : m_children)
        if (const SPtr<CRenderable> ptrRnd = ptrRenderer->GetRenderable(it))
            ptrRnd->Update();
}
