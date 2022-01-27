#include "cpassmanager.h"
#include "cbase.h"
#include "ccamera.h"
#include "clogger.h"

using namespace agl;

//---------------------------------------------------------------
CPassManager::CPassManager() :
    m_backColor(0.2, 0.2, 0.2, 1.0) {

    //----------------- initializing quad -------------------------
    m_screenQuad.vertexArray[0] =  1.0f;
    m_screenQuad.vertexArray[1] =  1.0f;

    m_screenQuad.vertexArray[2] = -1.0f;
    m_screenQuad.vertexArray[3] =  1.0f;

    m_screenQuad.vertexArray[4] =  1.0f;
    m_screenQuad.vertexArray[5] = -1.0f;

    m_screenQuad.vertexArray[6] = -1.0f;
    m_screenQuad.vertexArray[7] = -1.0f;

    m_screenQuad.textureArray[0] = 1.0f;
    m_screenQuad.textureArray[1] = 1.0f;

    m_screenQuad.textureArray[2] = 0.0f;
    m_screenQuad.textureArray[3] = 1.0f;

    m_screenQuad.textureArray[4] = 1.0f;
    m_screenQuad.textureArray[5] = 0.0f;

    m_screenQuad.textureArray[6] = 0.0f;
    m_screenQuad.textureArray[7] = 0.0f;

    //------------- buffers for the display quad
    glGenBuffers(1, &m_screenQuad.vertex);
    glBindBuffer(GL_ARRAY_BUFFER, m_screenQuad.vertex);
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), m_screenQuad.vertexArray, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &m_screenQuad.texture);
    glBindBuffer(GL_ARRAY_BUFFER, m_screenQuad.texture);
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), m_screenQuad.textureArray, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //----------------------------------------------------------------------------------
}

//---------------------------------------------------------------
CPassManager::~CPassManager() {
    glDeleteBuffers(1, &m_screenQuad.vertex);
    glDeleteBuffers(1, &m_screenQuad.texture);
}

//---------------------------------------------------------------
void CPassManager::Setup(uint frameWidth_, uint frameHeight_) {

    // Default system framebuffer
    m_frameBuffers.pass[ePass_default].fbo = 0;

    //---------------------------------- screen color texture -------------------------------------
    glGenTextures(1, &m_frameBuffers.pass[ePass_1].tex);
    glBindTexture(GL_TEXTURE_2D, m_frameBuffers.pass[ePass_1].tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frameWidth_, frameHeight_, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);

    //---------------------------------- depth buffer -------------------------------------
    glGenRenderbuffers(1, &m_frameBuffers.rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_frameBuffers.rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, frameWidth_, frameHeight_);

    //---------------------------------- frame buffer -------------------------------------
    glGenFramebuffers(1, &m_frameBuffers.pass[ePass_1].fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffers.pass[ePass_1].fbo);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_frameBuffers.pass[ePass_1].tex, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_frameBuffers.rbo);

    GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, drawBuffers);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        CBase::GetBase()->GetLogger()->Write("FrameBuffer for GL_COLOR_ATTACHMENT0 is not complete");
        }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//---------------------------------------------------------------
void CPassManager::RenderScene(ePassName destination_) {

    glEnable(GL_DEPTH_TEST);

    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffers.pass[destination_].fbo);
}

//---------------------------------------------------------------
void CPassManager::ClearPass(ePassName destination_, GLbitfield bitfield_)
{
    glClearColor(m_backColor.r, m_backColor.g, m_backColor.b, m_backColor.a);

    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffers.pass[destination_].fbo);

    glClear(bitfield_);
}

//---------------------------------------------------------------
void CPassManager::RenderFbo(ePassName source_, ePassName destination_, TShaderName name_) {

    glDisable(GL_DEPTH_TEST);

    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffers.pass[destination_].fbo);
    glClear(GL_COLOR_BUFFER_BIT);

    SPtr<CShader> ptrShader = CBase::GetBase()->GetShader();
    if (!ptrShader)
        return;

    const TShaderProgram&       shaderId   = ptrShader->GetProgram(name_);
    const TShaderPropsLocation& properties = ptrShader->GetProperties(shaderId);

    glUseProgram(shaderId);

    SPtr<CCamera> ptrCamera = CBase::GetBase()->GetCamera();

    ptrCamera->GetMemento()->PushState();

    ptrCamera->SetViewVolume(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    ptrCamera->SetProjectionType(eOrtho);

    auto itPrj = properties.find(eProjectionMatr);
    glUniformMatrix4fv(itPrj->second.location, 1, GL_FALSE, &ptrCamera->GetProjectionMat()[0][0]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_frameBuffers.pass[source_].tex);
    glUniform1i(glGetUniformLocation(shaderId, "texture0"), 0);

    glEnableVertexAttribArray(eVertCoord);
    glBindBuffer(GL_ARRAY_BUFFER, m_screenQuad.vertex);
    glVertexAttribPointer(eVertCoord, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(eVertTexCoord);
    glBindBuffer(GL_ARRAY_BUFFER, m_screenQuad.texture);
    glVertexAttribPointer(eVertTexCoord, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisableVertexAttribArray(eVertCoord);
    glDisableVertexAttribArray(eVertTexCoord);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    ptrCamera->GetMemento()->PopState();
}

