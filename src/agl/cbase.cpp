#ifdef _WEB
#include <GLES3/gl3.h>
#include <emscripten.h>
#endif

#include "tinyxml2.h"

#include "cbase.h"
#include "crenderable.h"
#include "crenderer.h"
#include "clogger.h"
#include "cshader.h"
#include "ccamera.h"
#include "ctransform.h"

#ifdef _WEB
#include "../misc/jsutils.h"
#endif

#include "cwndmanager.h"

using namespace agl;
using namespace tinyxml2;

SPtr<CBase> CBase::m_ptrBase = nullptr;

//---------------------------------------------------------------
CBase::CBase() {
    }

//---------------------------------------------------------------
CBase::~CBase() {
    m_ptrCamera     = nullptr;
    m_ptrTransforms = nullptr;
    m_ptrRenderer   = nullptr;
    m_ptrShader     = nullptr;
    m_ptrWndManager = nullptr;
    m_ptrObserver   = nullptr;
    m_ptrLogger     = nullptr;
    }

//---------------------------------------------------------------
SPtr<CBase> CBase::GetBase() {
    if (!m_ptrBase)
        m_ptrBase = std::make_shared<CBase>();

    return m_ptrBase;
    }

//---------------------------------------------------------------
void CBase::Init() {
   m_ptrLogger = std::make_shared<CLogger>();
    if (!m_ptrLogger) {
        printf("Couldn't create logger \n");
        return;
    }

    m_ptrObserver = std::make_shared<bu::CObserver<eBASEEVENT>>();
    if (!m_ptrObserver) {
        m_ptrLogger->Write("Couldn't create Observer");
        return;
    }

    m_ptrWndManager = std::make_shared<CWndManager>();
    if (!m_ptrWndManager) {
        m_ptrLogger->Write("Couldn't create Window manager");
        return;
    }

    if (!m_ptrWndManager->InitContext()) {
        m_ptrLogger->Write("Couldn't create GL context");
        return;
    }

    m_ptrTransforms = std::make_shared<CTransform>();
    if (!m_ptrTransforms) {
        m_ptrLogger->Write("Couldn't create Transforms");
        return;
    }

    m_ptrShader = std::make_shared<CShader>();
    if (!m_ptrShader) {
        m_ptrLogger->Write("Couldn't create Shader system");
        return;
    }

    m_ptrRenderer = std::make_shared<CRenderer>(this);
    if (!m_ptrRenderer) {
        m_ptrLogger->Write("Couldn't create Renderer system");
        return;
    }

    if (!readConfigure()) {
        m_ptrLogger->Write("Couldn't init graphics on config data");
        return;
    }

    m_ptrLogger->Write("Successful init of graphics core");
}

//---------------------------------------------------------------
SPtr<CWndManager> CBase::GetWndManager() {
    return m_ptrWndManager;
}

//---------------------------------------------------------------
SPtr<CTransform> CBase::GetTransform() {
    return m_ptrTransforms;
}

//---------------------------------------------------------------
SPtr<bu::CObserver<CBase::eBASEEVENT>> CBase::GetObserver() {
    return m_ptrObserver;
}

//---------------------------------------------------------------
void CBase::Update() {
    m_ptrRenderer->Update();
}

//---------------------------------------------------------------
bool CBase::readConfigure() {

    // Reading configuration from file
    SPtr<XMLDocument> pInconf(std::make_shared<XMLDocument>());

    if (pInconf->LoadFile("./filesystem/confbase.xml") != XML_NO_ERROR) {
        m_ptrLogger->Write("Could not load confbase.xml");
        return false;
        }

    XMLElement *pConf = pInconf->FirstChildElement("Configuration");
    XMLElement *pRoot, *pInelem;

    pRoot = pConf->FirstChildElement("Display");
        {
        int ResX, ResY;
        pInelem = pRoot->FirstChildElement("ResX");
        ResX = pInelem->IntAttribute("val");
        pInelem = pInelem->NextSiblingElement("ResY");
        ResY = pInelem->IntAttribute("val");

        m_ptrWndManager->SetResolution(ResX, ResY);

        CRenderer::SMode mode;

        pInelem = pInelem->NextSiblingElement("Antialiase");
        mode.Antialiase = pInelem->IntAttribute("val");

        pInelem = pInelem->NextSiblingElement("AntialiseLevel");
        mode.AntialiaseLevel = pInelem->IntAttribute("val");

        m_ptrRenderer->SetMode(mode);

        pInelem = pInelem->NextSiblingElement("Fullscreen");     
        m_ptrRenderer->SetFullscreen(pInelem->IntAttribute("val"));

        CColor<float> cVal;
        pInelem = pInelem->NextSiblingElement("BackColor");
        pInelem->QueryFloatAttribute("R", &cVal.r);
        pInelem->QueryFloatAttribute("G", &cVal.g);
        pInelem->QueryFloatAttribute("B", &cVal.b);
        pInelem->QueryFloatAttribute("A", &cVal.a);
        m_ptrRenderer->SetBackgroundClr(cVal);
        }

    pRoot = pConf->FirstChildElement("Camera");
        {
        pInelem = pRoot->FirstChildElement("Type");

        m_ptrCamera = std::make_shared<CCamera>();

        float varVal;

        if (eCAMTYPE(pInelem->IntAttribute("val")) == ePerspective) {

            pInelem = pInelem->NextSiblingElement("Fov");
            pInelem->QueryFloatAttribute("val", &varVal);
            m_ptrCamera->SetFov(varVal);

            pInelem = pInelem->NextSiblingElement("NearPlane");
            pInelem->QueryFloatAttribute("val", &varVal);
            m_ptrCamera->SetNearPlane(varVal);

            pInelem = pInelem->NextSiblingElement("FarPlane");
            pInelem->QueryFloatAttribute("val", &varVal);
            m_ptrCamera->SetFarPlane(varVal);
            }

        if (eCAMTYPE(pInelem->IntAttribute("val")) == eOrtho) {

            float l, r, b, t, n, f;
            pInelem = pInelem->NextSiblingElement("LeftBrd");
            l = pInelem->IntAttribute("val");
            pInelem = pInelem->NextSiblingElement("RightBrd");
            r = pInelem->IntAttribute("val");
            pInelem = pInelem->NextSiblingElement("BottomBrd");
            b = pInelem->IntAttribute("val");
            pInelem = pInelem->NextSiblingElement("TopBrd");
            t = pInelem->IntAttribute("val");
            pInelem = pInelem->NextSiblingElement("NearBrd");
            n = pInelem->IntAttribute("val");
            pInelem = pInelem->NextSiblingElement("FarBrd");
            f = pInelem->IntAttribute("val");
            m_ptrCamera->SetViewVolume(l, r, b, t, n, f);
            }
        }

    return true;
    }

//---------------------------------------------------------------
SPtr<CCamera> CBase::GetCamera() {
    return m_ptrCamera;
    }

//---------------------------------------------------------------
SPtr<CLogger> CBase::GetLogger() {
    return m_ptrLogger;
    }

//---------------------------------------------------------------
SPtr<CRenderer> CBase::GetRenderer() {
    return m_ptrRenderer;
    }

//---------------------------------------------------------------
SPtr<CShader> CBase::GetShader() {
    return m_ptrShader;
    }
