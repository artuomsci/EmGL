#ifndef CCONE_H
#define CCONE_H

#include "basicdefs.h"
#include "../crenderable.h"

namespace agl {

class CCone : public CRenderable {

    public:

    CCone();

     void            SetHeight(double val_);
     double          GetHeight() const;
     void            SetRadius(double val_);
     double          GetRadius() const;
     void            SetUSubdiv(uint val_);
     uint            GetUSubdiv() const;
     void            SetVSubdiv(uint val_);
     uint            GetVSubdiv() const;
     CMaterial*      GetMaterial();

    private:

        void initGeometry();

        double  m_radius, m_height;
        uint    m_subdivRadial, m_subdivConcentric;
    };
}

#endif
