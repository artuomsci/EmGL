#ifndef CWNDMANAGER
#define CWNDMANAGER

#ifdef _WEB
#include <html5.h>
#endif

#include <memory>

#include "iwindow.h"

namespace agl {

class CWndManager {

public:

    CWndManager();
    ~CWndManager();

    bool InitContext();
    void SetResolution(uint width_, uint height_);
    void GetResolution(uint& width_, uint& height_) const;

    void LoopCallback(const std::function<void()>& loop_);

private:

    void resizeWindowCallback();

#ifdef _WEB
        // WebGL canvas attributes
        EmscriptenWebGLContextAttributes    m_attrs;
        // WebGL context
        EMSCRIPTEN_WEBGL_CONTEXT_HANDLE     m_context;
#endif

    std::shared_ptr<IWindow> m_ptrWnd;
};

}

#endif // CWNDMANAGER

