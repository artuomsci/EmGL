#define GLM_FORCE_CXX14
#define GLM_FORCE_PURE
#define GLM_FORCE_INLINE

/**< Emscripten libraries */
#ifdef _WEB
#include <emscripten/emscripten.h>
#endif

/**< Standard libraries */
#include <stdlib.h>
#include <memory>
#include <fstream>
/**< External libraries */

/**< Custom sources */
#include "./agl/cbase.h"
#include "./agl/cwndmanager.h"
#include "./agl/cinput.h"

//---------------------------------------------------------------
SPtr<agl::CBase>        g_ptrBase;

// External JavaScript calls
#ifdef _WEB
#include "../misc/htmlgui.h"
#endif

//---------------------------------------------------------------
void Loop() {
        g_ptrBase->Update();
    }

int main() {

    g_ptrBase = agl::CBase::GetBase();
    g_ptrBase->Init();

    g_ptrBase->GetWndManager()->LoopCallback(std::bind(&agl::CBase::Update, g_ptrBase));

    agl::CInput::HookUp();

#ifdef _WEB
    emscripten_set_main_loop(Loop, 0, 1);

    emscripten_exit_with_live_runtime();
#endif

    g_ptrBase = nullptr;

    return 0;
    }






