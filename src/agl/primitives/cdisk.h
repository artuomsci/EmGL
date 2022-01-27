#ifndef CDISK_H
#define CDISK_H

#include "basicdefs.h"
#include "../crenderable.h"

namespace agl {

class CDisk : public CRenderable {

    public:

    CDisk();

     void            SetRadius(double val_);
     double          GetRadius() const;
     void            SetSubdiv(uint val_);
     uint            GetSubdiv() const;
     CMaterial*      GetMaterial();

    private:

        void initGeometry();

        double  m_radius;
        uint    m_subdivision;
    };

}

#endif
