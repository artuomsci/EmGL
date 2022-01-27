#ifndef CQUAD_H
#define CQUAD_H

#include "basicdefs.h"
#include "../crenderable.h"

namespace agl {

class CQuad : public CRenderable {

    public:

        CQuad();
        ~CQuad() {}

         void            UpdateNormals();
         void            SetWidth(double val_);
         double          GetWidth() const;
         void            SetHeight(double val_);
         double          GetHeight() const;
         void            SetSubdivision(double val_);
         double          GetSubdivision() const;
         CMaterial*      GetMaterial();

    private:

        void initGeometry();

        const static std::vector<aVec3> svArr;

        double  m_width, m_height;
        int     m_subdiv;
};

}

#endif
