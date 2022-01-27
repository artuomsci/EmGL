#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "basicdefs.h"
#include "../crenderable.h"

namespace agl {

class CTriangle : public CRenderable {

    public:

    CTriangle();

     void            UpdateNormals();
     void            SetPosition(const aVec3& P0, const aVec3& P1, const aVec3& P2);
     CMaterial*      GetMaterial();
};

}

#endif
