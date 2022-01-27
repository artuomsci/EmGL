#ifndef CRENDERER_H
#define CRENDERER_H

#include <vector>
#include <chrono>
#include <map>

#include "classutils.h"
#include "ccolor.hpp"
#include "basicdefs.h"
#include "cpassmanager.h"
#include "cimgui.h"

namespace agl {

class CBase;
class CRenderable;

class CRenderer {

        friend class CRenderable;

    public:

        typedef std::unordered_map<nodeId, SPtr<CRenderable>> TRenderableMap;

        struct SMode {
            uint DepthBits;
            uint AlphaBits;
            uint StensilBits;
            bool Antialiase;
            uint AntialiaseLevel;
            SMode() :
              DepthBits(16)
            , AlphaBits(8)
            , StensilBits(8)
            , Antialiase(false)
            , AntialiaseLevel(2) {}
        };

        CRenderer(CBase* base_);
        ~CRenderer();

        void Update();
        void SetViewport(const SViewport& viewport_);
        long GetFrameCount() const;
        void SetMode(const SMode& mode_);
        const SMode& GetMode() const;
        void SetFullscreen(bool state_);
        void SetBackgroundClr(const CColor<float>& color_);
        const CColor<float>& GetBackgroundClr() const;
        const SPtr<CRenderable> GetRenderable(nodeId id_) const;
        const TRenderableMap& GetRenderables() const;
        void AddRenderable(SPtr<CRenderable> ptrRenderable_);
        void RemoveRenderable(nodeId id_);
        CImGui& GetGui();

    private:

        void init();
        void onResolutionChange();

        NO_COPY_CLASS(CRenderer)

        CBase*          m_base;
        long            m_frameCount;
        uint            m_wndWidth;
        uint            m_wndHeight;
        SMode           m_mode;
        bool            m_fullScr;
        CColor<float>   m_backColor;
        CPassManager    m_passmanager;

        CImGui          m_gui;

        TRenderableMap                              m_renderables;
    };

}

#endif
