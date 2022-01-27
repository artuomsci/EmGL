#ifndef CMATERIAL_H
#define CMATERIAL_H

#ifdef _WEB
#include <GLES3/gl3.h>
#endif

#include "cimage.h"
#include "ccolor.hpp"
#include "cshader.h"

namespace agl {

enum eTEXTURETYPE   { eDiffuseTex, eNormalTex, eSpecularTex, eMiscTex };
enum eCOLORTYPE     { eDiffuseClr, eAmbientClr, eSpecularClr };

class CMaterial {

    public:

        CMaterial();
        ~CMaterial();
        bool            IsTextured(void) const;
        CImage*         GetTexture(const eTEXTURETYPE type_);
        GLuint          GetTextureID(const eTEXTURETYPE type_) const;
        void            SetColor(eCOLORTYPE type_, const CColor<float> &color_);
        void            SetColor(eCOLORTYPE type_, float r, float g, float b, float a);
        CColor<float>&  GetColor(eCOLORTYPE type_);
        void            SetShine(float koef_);
        float&          GetShine(void);
        bool            IsTwoSided(void);
        void            SetTwoSided(bool state_);
        TShaderProgram  GetShaderProgram();
        void            SetShaderProgram(const TShaderName& name_);
        const TShaderPropsData& GetProperties() const;

    private:

        std::vector<CImage> m_textures;

        TShaderProgram   m_shaderProgram;
        TShaderPropsData m_matProperties;

        CColor<float>   m_colorDiff, m_colorAmb, m_colorSpec;
        float           m_shine;
        bool            m_bTwoSided;
        bool            m_bTextured;
    };
}

#endif
