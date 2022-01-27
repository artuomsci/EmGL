#include "jsutils.h"

//================================================
// Interface export functions for javascript
// These functions are going to be called from
// outside by javascript so we have to prevent
// С++ name mangling
//================================================

extern "C"
{
    void EMSCRIPTEN_KEEPALIVE SetResolution(int wndWidth_, int wndHeight_) {
        if (!agl::CBase::GetBase())
            return;
        agl::CBase::GetBase()->GetRenderer()->SetResolution(wndWidth_, wndHeight_);
        }

    void EMSCRIPTEN_KEEPALIVE SaveDataOnDisk() {
        sim::CSimworld::Getsim()->GetEditor().SaveData();
        }

    void EMSCRIPTEN_KEEPALIVE LoadDataFromDisk(char* pFileName_) {
        sim::CSimworld::Getsim()->GetEditor().LoadData(pFileName_);
        }
}
