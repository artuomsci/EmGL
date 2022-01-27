#ifndef CCIRCLE_H
#define CCIRCLE_H

#include "basicdefs.h"
#include "../crenderable.h"

namespace agl {

class CCircle : public CRenderable {

    public:

    CCircle();

                     ~CCircle() {}
     void            SetRadius(double val_);
     double          GetRadius() const;
     void            SetSubdiv(uint val_);
     int             GetSubdiv() const;
     CMaterial*      GetMaterial();

    private:

    void initGeometry();

    double  m_radius;
    uint    m_subdivision;
};

}

#endif // CCIRCLE_H
