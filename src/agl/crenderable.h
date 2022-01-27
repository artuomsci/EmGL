#ifndef CRENDERABLE_H
#define CRENDERABLE_H

#include "basicdefs.h"
#include "cmaterial.h"
#include "cnode.h"
#include "cmesh.h"

namespace agl {

class CBase;

class CRenderable : public CNode {

    friend class CVisualizer;
    friend class CBase;

    public:

        CRenderable();
        virtual         ~CRenderable();

        void            Render();
        void            SetVisible(bool state_);
        bool            IsVisible() const;
        CMaterial&      GetMaterial();

    private:

        SPtr<CBase>     m_ptrBase;
        bool            m_bVisible;

    protected:

        CMaterial       m_material;
        CMesh           m_mesh;
    };
}

#endif
