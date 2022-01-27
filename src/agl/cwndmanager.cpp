#include "iwindow.h"
#include "cglfwwindow.h"
#include "cwndmanager.h"
#include "cbase.h"
#include "clogger.h"

using namespace agl;

//---------------------------------------------------------------
CWndManager::CWndManager() :
    m_ptrWnd    (nullptr) {
}

//---------------------------------------------------------------
CWndManager::~CWndManager() {
    if (m_ptrWnd)
        m_ptrWnd->Close();

#ifdef _WEB
    emscripten_webgl_destroy_context(m_context);
//    emscripten_async_call(final, (void*)0, 10);
#endif
}

//---------------------------------------------------------------
bool CWndManager::InitContext() {

#ifdef _WEB
    emscripten_webgl_init_context_attributes(&m_attrs);

    /**< Defining WebGL canvas attributes */
    m_attrs.depth = true;
    m_attrs.stencil = true;
    m_attrs.antialias = true;
    m_attrs.majorVersion = 1;
    m_attrs.minorVersion = 0;
    m_attrs.enableExtensionsByDefault = true;

    m_context = emscripten_webgl_create_context(0, &m_attrs);
    if (m_context < 0)
        return false;

    emscripten_webgl_make_context_current(m_context);

    emscripten_webgl_enable_extension(m_context, "OES_vertex_array_object");

#endif

    m_ptrWnd.reset(new CGLFWwindow);
    if (!m_ptrWnd)
        return false;

    if (!m_ptrWnd->CreateWindow(640, 480, 0, false)) {
        printf("Could not create window \n");
        return false;
    }

    m_ptrWnd->ResizeWindowCallback(std::bind(&CWndManager::resizeWindowCallback, this));

    /**< Requesting GL version */
    SPtr<CLogger> ptrLogger = CBase::GetBase()->GetLogger();
    const char* pRenderer = (char*)glGetString (GL_RENDERER);
    ptrLogger->Write(std::string(pRenderer));
    const char* pVersion = (char*)glGetString (GL_VERSION);
    ptrLogger->Write(std::string(pVersion));
    const char* pGlsl = (char*)glGetString (GL_SHADING_LANGUAGE_VERSION);
    ptrLogger->Write(std::string(pGlsl));

    return true;
    }

//---------------------------------------------------------------
void CWndManager::LoopCallback(const TEmptyFunc& loop_) {
    if (m_ptrWnd)
        m_ptrWnd->LoopCallback(loop_);
}

//---------------------------------------------------------------
void CWndManager::SetResolution(uint width_, uint height_) {

    if (m_ptrWnd)
        m_ptrWnd->ResizeWindow(width_, height_);

    CBase::GetBase()->GetObserver()->SignalFunc(CBase::eResolutionChange);
}

//---------------------------------------------------------------
void CWndManager::GetResolution(uint& width_, uint& height_) const {
    if (m_ptrWnd)
        m_ptrWnd->GetWindowSize(width_, height_);
}

//---------------------------------------------------------------
void CWndManager::resizeWindowCallback() {
    CBase::GetBase()->GetObserver()->SignalFunc(CBase::eResolutionChange);
}
