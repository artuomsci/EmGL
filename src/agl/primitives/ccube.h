#ifndef CCUBE_H
#define CCUBE_H

#include "basicdefs.h"
#include "../crenderable.h"

namespace agl {

class CCube : public CRenderable {

    public:

        CCube();
       ~CCube() {}

         void            SetWidth(double val_);
         double          GetWidth() const;
         void            SetHeight(double val_);
         double          GetHeight() const;
         void            SetLength(double val_);
         double          GetLength() const;
         CMaterial*      GetMaterial();

    private:

        void initGeometry();

        const static std::vector<aVec3> svArr;
        const static std::vector<aVec3> snArr;
        const static std::vector<aVec3> sbArr;
        const static std::vector<uint>  siArr;

        double m_width, m_height, m_length;
    };
}

#endif
