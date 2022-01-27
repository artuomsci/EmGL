#ifndef CCYLINDER_H
#define CCYLINDER_H

#include "basicdefs.h"
#include "../crenderable.h"
#include "ctriangle.h"
#include "cquad.h"

namespace agl {

class CCylinder : public CRenderable {

    public:

    CCylinder();
    ~CCylinder();

     void            SetRadius(double val_);
     double          GetRadius() const;
     void            SetHeight(double val_);
     double          GetHeight() const;
     void            SetSubdiv(uint val_);
     uint            GetSubdiv() const;
     CMaterial*      GetMaterial();

    private:

        void initGeometry();

        double  m_radius, m_height;
        uint    m_subdivision;
};

}

#endif
