#ifndef CLINE_H
#define CLINE_H

#include "basicdefs.h"
#include "../crenderable.h"

namespace agl {

class CLine : public CRenderable {

    public:

                CLine();
                CLine(const aVec3& p0_, const aVec3& p1_);
               ~CLine() {}

         void            SetPosition(const aVec3& p0_, const aVec3& p1_);
         void            GetPosition(aVec3& p0_, aVec3& p1_) const;
         void            SetLength(double val_);
         double          GetLength() const;
         void            SetWidth(float width_);
         float           GetWidth() const;
         CMaterial*      GetMaterial();

    private:

        double m_length;
    };
}

#endif
