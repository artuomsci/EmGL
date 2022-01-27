#ifndef CSPHERE_H
#define CSPHERE_H

#include "basicdefs.h"
#include "../crenderable.h"

namespace agl {

class CSphere : public CRenderable {

    public:

    CSphere();

     void            SetRadius(double val_);
     double          GetRadius() const;
     void            SetUSubdiv(uint val_);
     uint            GetUSubdiv() const;
     void            SetVSubdiv(uint val_);
     uint            GetVSubdiv() const;
     CMaterial*      GetMaterial();

    private:

        void initGeometry();

        double  m_radius;
        uint    m_longSubdiv, m_latSubdiv;
};

}

#endif
