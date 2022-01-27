#ifndef CPOINT_H
#define CPOINT_H

#include "basicdefs.h"
#include "../crenderable.h"

namespace agl {

class CPoint : public CRenderable {

    public:

        CPoint();
        CPoint(const aVec3& vec_);
       ~CPoint() {}

         float           GetSize() const;
         void            SetSize(float size_);
         void            SetPosition(const aVec3& vec_);
         void            GetPosition(aVec3& vec_) const;
         CMaterial*      GetMaterial();

    private:

        float   m_pntSize;
    };
}

#endif
