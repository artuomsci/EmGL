#ifndef CPASS_MANAGER_H
#define CPASS_MANAGER_H

#include <GL/glew.h>

#ifdef _WEB
#include <GLES3/gl3.h>
#endif

#include "basicdefs.h"
#include "cshader.h"
#include "ccolor.hpp"

namespace agl {

class CPassManager
{
 public:

    enum ePassName {
        ePass_default,
        ePass_1,
        ePass_2,
        ePass_3,
        ePass_4,
        ePass_end
    };

    struct SFboData {
        uint fbo; uint tex;

        SFboData() : fbo(0), tex(0) {}
    };

    struct SFrameBuffer {
        SFboData    pass[ePass_end];
        uint        rbo;
    };

    struct SPostProcQuad {
        float   vertexArray[8];
        float   textureArray[8];
        uint    vao;
        uint    vertex;
        uint    texture;

        SPostProcQuad() : vao(0), vertex(0), texture(0) {}
    };

    CPassManager();
    ~CPassManager();

    void Setup(uint frameWidth_, uint frameHeight_);
    void RenderFbo(ePassName source_, ePassName destination_, TShaderName name_);
    void RenderScene(ePassName destination_);
    void ClearPass(ePassName destination_, GLbitfield bitfield_);

private:

    SFrameBuffer    m_frameBuffers;
    SPostProcQuad   m_screenQuad;
    CColor<float>   m_backColor;

};

}

#endif
