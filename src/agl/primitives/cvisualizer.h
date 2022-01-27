#ifndef CVISUALIZER_H
#define CVISUALIZER_H

//=================================================
//      This class helps to visualize normals
//=================================================

#include "../agl/crenderable.h"

namespace  agl {

class CVisualizer : public CRenderable
{

public:

    CVisualizer();
    void            Update(CRenderable* renderable_, float scale_ = 1.0f);
    CMaterial*      GetMaterial();
};

}

#endif // CVISUALIZER_H
