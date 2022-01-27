#include "cmaterial.h"
#include "cbase.h"

using namespace agl;

//---------------------------------------------------------------
CMaterial::CMaterial() :
        m_shine     (1.0f)
    ,   m_colorDiff (1.0f, 1.0f, 1.0f, 1.0f)
    ,   m_colorAmb  (1.0f, 1.0f, 1.0f, 1.0f)
    ,   m_colorSpec (1.0f, 1.0f, 1.0f, 1.0f)
    ,   m_bTextured (false)
    ,   m_bTwoSided (false) {
    }

//---------------------------------------------------------------
CMaterial::~CMaterial() {
    }

//---------------------------------------------------------------
bool CMaterial::IsTextured(void) const {
    return m_bTextured;
    }

//---------------------------------------------------------------
void CMaterial::SetShine(float koef_) {
    m_shine = koef_;

    if (m_matProperties.count(eShininess))
            m_matProperties[eShininess].f1 = koef_;
    }

//---------------------------------------------------------------
float& CMaterial::GetShine(void) {
    return m_shine;
    }

//---------------------------------------------------------------
void CMaterial::SetColor(eCOLORTYPE type_, const CColor<float>& color_) {
    switch (type_) {
        case eDiffuseClr:
        {
            m_colorDiff = color_;

            if (m_matProperties.count(eDiffuse))
                m_matProperties[eDiffuse].v3 = aVec3(color_.r, color_.g, color_.b);

        }
            break;
        case eSpecularClr:
        {
            m_colorSpec = color_;

            if (m_matProperties.count(eSpecular))
                m_matProperties[eSpecular].v3 = aVec3(color_.r, color_.g, color_.b);

        }
            break;
        case eAmbientClr:
        {
            m_colorAmb = color_;

            if (m_matProperties.count(eAmbient))
                m_matProperties[eAmbient].v3 = aVec3(color_.r, color_.g, color_.b);
        }
            break;
        }
    }

//---------------------------------------------------------------
void CMaterial::SetColor(eCOLORTYPE type_, float r, float g, float b, float a) {
        SetColor(type_, CColor<float>(r, g, b, a));
    }

//---------------------------------------------------------------
CColor<float>& CMaterial::GetColor(eCOLORTYPE type_) {
    switch (type_) {
        case eDiffuseClr:
            return m_colorDiff;
        case eSpecularClr:
            return m_colorSpec;
        case eAmbientClr:
            return m_colorAmb;
        }
    }

//---------------------------------------------------------------
GLuint CMaterial::GetTextureID(const eTEXTURETYPE type_) const {
        return 0;
    }

//---------------------------------------------------------------
CImage* CMaterial::GetTexture(const eTEXTURETYPE type_) {
        return nullptr;
    }

//---------------------------------------------------------------
bool CMaterial::IsTwoSided(void) {
    return m_bTwoSided;
    }

//---------------------------------------------------------------
void CMaterial::SetTwoSided(bool state_) {
    m_bTwoSided = state_;
    }

//---------------------------------------------------------------
TShaderProgram CMaterial::GetShaderProgram() {
    return m_shaderProgram;
    }

//---------------------------------------------------------------
void CMaterial::SetShaderProgram(const TShaderName& name_) {
        SPtr<CShader> ptrShader = CBase::GetBase()->GetShader();
        if (!ptrShader)
            return;

        auto it = ptrShader->GetLibrary().find(name_);
        m_shaderProgram = it->second;

        const TShaderPropsLocation& propsdata = ptrShader->GetProperties(name_);
        for (TShaderPropsLocation::const_iterator it = propsdata.begin(); it != propsdata.end(); ++it)
            m_matProperties[it->first] = SUniformsData();
    }

//---------------------------------------------------------------
const TShaderPropsData& CMaterial::GetProperties() const {
        return m_matProperties;
    }

