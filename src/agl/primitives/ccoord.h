#ifndef CCOORD_H
#define CCOORD_H

#include "../misc/basicdefs.h"

namespace agl {

class CPoint;
class CLine;

class CCoord
{

public:

    CCoord();
    void SetSize(float size_);

private:

    void update();

    SPtr<agl::CLine>     m_ptrAxisX, m_ptrAxisY, m_ptrAxisZ;
    SPtr<agl::CPoint>    m_ptrCentralPoint;
    float                m_size;
};

}

#endif // CCOORD_H
