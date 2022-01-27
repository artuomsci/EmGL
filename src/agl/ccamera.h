#ifndef CCAMERA_H
#define CCAMERA_H

#include <vector>

#include "basicdefs.h"
#include "cnode.h"
#include "classutils.h"

namespace agl {

// Type of camera projection
enum eCAMTYPE { ePerspective, eOrtho };

class CMemCamera;

class CCamera {

    public:

        CCamera();
        ~CCamera();

        void            SetProjectionType(const eCAMTYPE type_);
        eCAMTYPE        GetProjectionType() const;
        void            IdentityTransform();
        void            SetPosition(const aVec3& vec_);
        void            GetPosition(aVec3& vec_) const;
        void            SetOrientation(const aQuat& quat_);
        void            GetOrientation(aQuat& quat_) const;
        const aMat4&    GetModelViewMat() const;
        const aMat4&    GetProjectionMat() const;
        const aMat4&    GetModNormalMat() const;
        void            SetNearPlane(const double in_);
        double          GetNearPlane() const;
        void            SetFarPlane(const double in_);
        double          GetFarPlane() const;
        void            SetFov(const double in_);
        double          GetFov() const;
        void            SetViewVolume(double left_, double right_, double bottom_, double top_, double near_, double far_);
        void            GetViewVolume(double &left_, double &right_, double &bottom_, double &top_, double &near_, double &far_) const;

        void            Update();

        SPtr<IMemento>  GetMemento();

    private:

        CNode       m_node;
        double      m_nearPlane, m_farPlane, m_fov;
        double      m_leftBr, m_rightBr, m_bottomBr, m_topBr, m_nearBr, m_farBr;
        eCAMTYPE    m_type;

        SPtr<IMemento> m_ptrMemCamera;
    };

class CMemCamera : public IMemento {

    public:

    CMemCamera(CCamera* pCamera_);

    // IMemento
    virtual void PushState();
    virtual void PopState();

    private:

    struct SCamState {
        CNode       node;
        double      nearPlane, farPlane, fov;
        double      leftBr, rightBr, bottomBr, topBr, nearBr, farBr;
        eCAMTYPE    type;
    };

    CCamera*                m_pCamera;
    std::vector<SCamState>  m_states;
};

}

#endif
