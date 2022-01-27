#ifndef CRECTANGLE_H
#define CRECTANGLE_H

#include "basicdefs.h"
#include "../crenderable.h"

namespace agl {

class CRectangle : public CRenderable
{

public:

    CMaterial* GetMaterial();

    CRectangle();
    ~CRectangle() {}

    double GetWidth() const;
    double GetHeight() const;
    void Get(double& x0_, double& y0_, double& x1_, double& y1_) const;
    void Set(double x0_, double y0_, double x1_, double y1_);
    void Set_P0(double x0_, double y0_);
    void Set_P1(double x1_, double y1_);

private:

    void initGeometry();

    CRect<double> m_rect;
};

}


#endif // CRECTANGLE_H
