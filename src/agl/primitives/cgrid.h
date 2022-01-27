#ifndef CGRID_H
#define CGRID_H

#include "basicdefs.h"
#include "../crenderable.h"

namespace agl {

class CGrid : public CRenderable {

    public:

        CGrid();
       ~CGrid() {}

         void            SetWidth(double val_);
         double          GetWidth() const;
         void            SetHeight(double val_);
         double          GetHeight() const;
         void            SetUSubdiv(uint val_);
         void            SetVSubdiv(uint val_);
         uint            GetUSubdiv() const;
         uint            GetVSubdiv() const;
         CMaterial*      GetMaterial();

    private:

        void initGeometry();

        double  m_width, m_height;
        uint    m_uSubdiv, m_vSubdiv;

        const static std::vector<aVec3> svArr;
    };
}

#endif // CGRID_H
