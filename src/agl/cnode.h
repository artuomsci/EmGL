#ifndef CNODE_H
#define CNODE_H

#include <vector>

#include "basicdefs.h"

namespace agl {

class CNode {

    public:

        enum eCOORD_TYPE { eLocal, eGlobal };

        CNode();
        virtual         ~CNode() {}

        void            SetTranslation(const aVec3& vec_);
        void            GetTranslation(aVec3& vec_) const;
        void            SetOrientation(const aQuat& quat_);
        void            GetOrientation(aQuat& quat_) const;
        bool            IsMovable() const;
        void            SetMovable(bool state_);
        nodeId          GetId() const;
        void            SetSelected(bool state_);
        bool            IsSelected() const;
        void            SetParent(nodeId id_);
        nodeId          GetParent() const;
        bool            HasParent() const;
        void            DetachParent();
        void            AddChild(nodeId id_);
        void            RemoveChild(nodeId id_);
        bool            HasChildren() const;
        void            Update();
        void            GetTransform(aQuat& quat_, eCOORD_TYPE type_) const;
        void            SetTransform(const aQuat& quat_);
        void            GetTransform(aVec3& vec_, eCOORD_TYPE type_) const;
        void            SetTransform(const aVec3& vec_);

    private:

        std::vector<nodeId> m_children;

        aQuat           m_orientationGlobal, m_orientationLocal;
        aVec3           m_posGlobal, m_posLocal;
        nodeId          m_id;
        nodeId          m_parentId;

        static nodeId   m_idCounter;

        bool            m_isMovable;
        bool            m_isSelected;
    };

}

#endif
