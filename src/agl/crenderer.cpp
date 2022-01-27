#ifdef _WEB
#include <emscripten/emscripten.h>
#include <GLES3/gl3.h>
#endif

#include "crenderer.h"
#include "cbase.h"
#include "ccamera.h"
#include "cshader.h"
#include "crenderable.h"
#include "cwndmanager.h"
#include "ctransform.h"

using namespace agl;

//---------------------------------------------------------------
CRenderer::CRenderer(CBase *base_) :
        m_base          (base_)
    ,   m_frameCount    (0)
    ,   m_wndWidth      (320)
    ,   m_wndHeight     (240)
    ,   m_fullScr       (false) {
        init();
    }

//---------------------------------------------------------------
CRenderer::~CRenderer() {
    }

//---------------------------------------------------------------
long CRenderer::GetFrameCount() const {
    return m_frameCount;
    }

//---------------------------------------------------------------
void CRenderer::SetMode(const CRenderer::SMode &mode_) {
   m_mode = mode_;
}

//---------------------------------------------------------------
const CRenderer::SMode& CRenderer::GetMode() const {
    return m_mode;
}

//---------------------------------------------------------------
void CRenderer::Update() {

    // Counting frames
    ++m_frameCount;

    //-------------------- Camera setup ----------------------------
    SPtr<CTransform> ptrTr = m_base->GetTransform();
    SPtr<CCamera> ptrCamera = m_base->GetCamera();
    aVec3 camPos; ptrCamera->GetPosition(camPos);
    ptrTr->Translate(camPos);
    aQuat camOrient; ptrCamera->GetOrientation(camOrient);
    ptrTr->Rotate(camOrient);

    m_base->GetObserver()->SignalFunc(CBase::eBASEEVENT::eGeometryPass, nullptr);

    //-------------------- Geometry pass ----------------------

    m_passmanager.ClearPass(CPassManager::ePass_1, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_passmanager.RenderScene(CPassManager::ePass_1);

    for (auto& it: m_renderables) {
        aVec3 translation; it.second->GetTranslation(translation);
        aQuat orientation; it.second->GetOrientation(orientation);

        ptrTr->SetNodeTransform(translation, orientation, it.second->IsMovable());

        it.second->Render();
        }

    m_passmanager.RenderScene(CPassManager::ePass_1);

    agl::CBase::GetBase()->GetCamera()->IdentityTransform();

    m_base->GetObserver()->SignalFunc(CBase::eBASEEVENT::eStartGuiPass, nullptr);

    m_passmanager.RenderFbo(CPassManager::ePass_1, CPassManager::ePass_default, "textureOutput");
    }

//---------------------------------------------------------------
void CRenderer::AddRenderable(SPtr<CRenderable> ptrRenderable_) {
    m_renderables[ptrRenderable_->GetId()] = ptrRenderable_;
    }

//---------------------------------------------------------------
CImGui& CRenderer::GetGui() {
    return m_gui;
}

//---------------------------------------------------------------
void CRenderer::RemoveRenderable(nodeId id_) {
    m_renderables.erase(id_);
    }

//---------------------------------------------------------------
void CRenderer::init() {

    glDisable(GL_BLEND);
    //glEnable(GL_CULL_FACE);
    glDisable(GL_CULL_FACE);

    CBase::GetBase()->GetObserver()->RegisterFunc(CBase::eResolutionChange, [this](void*) { this->onResolutionChange(); });
    }

//---------------------------------------------------------------
void CRenderer::SetViewport(const SViewport &viewport_) {

    m_wndWidth  = viewport_.GetWidth();
    m_wndHeight = viewport_.GetHeight();

    glViewport(0, 0, viewport_.GetWidth(), viewport_.GetHeight());

    SPtr<CCamera> ptrCamera = CBase::GetBase()->GetCamera();
    if (ptrCamera)
        ptrCamera->Update();

#ifdef _WEB
    emscripten_set_canvas_size(m_wndWidth, m_wndHeight);
#endif

    m_passmanager.Setup(m_wndWidth, m_wndHeight);

    m_gui.SetViewport(m_wndWidth, m_wndHeight);
    }

//---------------------------------------------------------------
void CRenderer::onResolutionChange() {
    CBase::GetBase()->GetWndManager()->GetResolution(m_wndWidth, m_wndHeight);
    SetViewport(SViewport(0, 0, m_wndWidth, m_wndHeight));
}

//---------------------------------------------------------------
void CRenderer::SetFullscreen(bool state_) {
    m_fullScr = state_;
    }

//---------------------------------------------------------------
const CColor<float>& CRenderer::GetBackgroundClr() const {
    return m_backColor;
    }

//---------------------------------------------------------------
const SPtr<CRenderable> CRenderer::GetRenderable(nodeId id_) const {
    CRenderer::TRenderableMap::const_iterator it = m_renderables.find(id_);
    if (it != m_renderables.end())
        return it->second;
    else
        return nullptr;
}

//---------------------------------------------------------------
const CRenderer::TRenderableMap& CRenderer::GetRenderables() const {
    return m_renderables;
}

//---------------------------------------------------------------
void CRenderer::SetBackgroundClr(const CColor<float>& color_) {
    m_backColor = color_;
    }
