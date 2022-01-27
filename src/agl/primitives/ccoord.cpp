#include "../cbase.h"
#include "../crenderer.h"
#include "ccoord.h"
#include "cline.h"
#include "cpoint.h"

using namespace agl;

CCoord::CCoord() :
    m_size(1.0f),
    m_ptrAxisX(std::make_shared<agl::CLine>()),
    m_ptrAxisY(std::make_shared<agl::CLine>()),
    m_ptrAxisZ(std::make_shared<agl::CLine>()),
    m_ptrCentralPoint(std::make_shared<agl::CPoint>()) {

    SPtr<agl::CRenderer> ptrRend = agl::CBase::GetBase()->GetRenderer();

    ptrRend->AddRenderable(m_ptrAxisX);
    ptrRend->AddRenderable(m_ptrAxisY);
    ptrRend->AddRenderable(m_ptrAxisZ);

    ptrRend->AddRenderable(m_ptrCentralPoint);

    m_ptrCentralPoint->GetMaterial()->SetColor(agl::eCOLORTYPE::eDiffuseClr, 0.8, 0.6, 0.8, 1.0);

    //------------------- Basis ---------------------
    m_ptrAxisX->SetParent(m_ptrCentralPoint->GetId());
    m_ptrAxisX->SetWidth(2.0);
    m_ptrAxisX->SetPosition(aVec3(0.0, 0.0, 0.0), aVec3(m_size, 0.0, 0.0));
    m_ptrAxisX->GetMaterial()->SetColor(agl::eCOLORTYPE::eDiffuseClr, 1.0, 0.0, 0.0, 1.0);

    m_ptrAxisY->SetParent(m_ptrCentralPoint->GetId());
    m_ptrAxisY->SetWidth(2.0);
    m_ptrAxisY->SetPosition(aVec3(0.0, 0.0, 0.0), aVec3(0.0, m_size, 0.0));
    m_ptrAxisY->GetMaterial()->SetColor(agl::eCOLORTYPE::eDiffuseClr, 0.0, 1.0, 0.0, 1.0);

    m_ptrAxisZ->SetParent(m_ptrCentralPoint->GetId());
    m_ptrAxisZ->SetWidth(2.0);
    m_ptrAxisZ->SetPosition(aVec3(0.0, 0.0, 0.0), aVec3(0.0, 0.0, m_size));
    m_ptrAxisZ->GetMaterial()->SetColor(agl::eCOLORTYPE::eDiffuseClr, 0.0, 0.0, 1.0, 1.0);
}

void CCoord::SetSize(float size_) {
    m_size = size_;
    update();
}

void CCoord::update() {
    m_ptrAxisX->SetPosition(aVec3(0.0, 0.0, 0.0), aVec3(m_size, 0.0, 0.0));
    m_ptrAxisY->SetPosition(aVec3(0.0, 0.0, 0.0), aVec3(0.0, m_size, 0.0));
    m_ptrAxisZ->SetPosition(aVec3(0.0, 0.0, 0.0), aVec3(0.0, 0.0, m_size));
}
