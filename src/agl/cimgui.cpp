#include <chrono>

#ifdef _WEB
#include <GLES3/gl3.h>
#endif

#include "cimgui.h"

#include "cbase.h"
#include "cshader.h"
#include "ccamera.h"
#include "cinput.h"
#include "cwndmanager.h"

using namespace agl;

//---------------------------------------------------------------
CImGui::CImGui() :
        m_FontTexture       (0)
    ,   m_ElementsHandle    (0)
    ,   m_VertexHandle      (0) {

    m_frameStartTime = std::chrono::system_clock::now();

    ImGuiIO& io = ImGui::GetIO();

    ImGuiStyle& style = ImGui::GetStyle();
    style.FrameRounding         = 0.8;
    style.ChildWindowRounding   = 4.0;
    style.CurveTessellationTol  = 1.0;
    style.FrameRounding         = 6.0;
    style.GrabRounding          = 4.0;
    style.WindowRounding        = 8.0;
    style.WindowFillAlphaDefault = 0.1;

    io.Fonts->AddFontFromFileTTF("./filesystem/fonts/ClearSans-Regular.ttf", 16, 0, io.Fonts->GetGlyphRangesCyrillic());

    createFontsTexture();

    glGenBuffers(1, &m_ElementsHandle);
    glGenBuffers(1, &m_VertexHandle);

    io.RenderDrawListsFn = nullptr;

    io.KeyMap[ImGuiKey_Tab]         = 91;
    io.KeyMap[ImGuiKey_LeftArrow]   = 18;
    io.KeyMap[ImGuiKey_RightArrow]  = 39;
    io.KeyMap[ImGuiKey_UpArrow]     = 38;
    io.KeyMap[ImGuiKey_DownArrow]   = 40;
    io.KeyMap[ImGuiKey_Delete]      = 46;
    io.KeyMap[ImGuiKey_Backspace]   = 8;
    io.KeyMap[ImGuiKey_Enter]       = 13;
    io.KeyMap[ImGuiKey_Escape]      = 27;

    CInput::events.RegisterFunc(CInput::eKeyUp,   [](void* keycode_) {
        unsigned long * keycode = static_cast<unsigned long *>(keycode_);
        ImGui::GetIO().KeysDown[*keycode] = false;
    });

    CInput::events.RegisterFunc(CInput::eKeyDown, [](void* keycode_) {
        unsigned long * keycode = static_cast<unsigned long *>(keycode_);
        ImGui::GetIO().KeysDown[*keycode] = true;
    });

    CInput::events.RegisterFunc(CInput::eKeyPress, [](void* charcode_) {
        unsigned long * charcode = static_cast<unsigned long *>(charcode_);
        if ((*charcode) != 0)
            ImGui::GetIO().AddInputCharacter(*charcode);
    });

    CInput::events.RegisterFunc(CInput::eMouseMove, [](void* mouseEvents_) {
        CInput::SMouseEvents* mouseEvents = static_cast<CInput::SMouseEvents*>(mouseEvents_);
        ImGui::GetIO().MousePos = ImVec2((float)mouseEvents->xPos, (float)mouseEvents->yPos);
    });

    CInput::events.RegisterFunc(CInput::eMouseDown, [](void* mouseEvents_) {
        CInput::SMouseEvents* mouseEvents = static_cast<CInput::SMouseEvents*>(mouseEvents_);

        if (mouseEvents->buttons & ((unsigned short)1 << 0))
            ImGui::GetIO().MouseDown[0] = true;

        if (mouseEvents->buttons & ((unsigned short)1 << 1))
            ImGui::GetIO().MouseDown[1] = true;
    });

    CInput::events.RegisterFunc(CInput::eMouseUp, [](void* mouseEvents_) {
        ImGui::GetIO().MouseDown[0] = false;
        ImGui::GetIO().MouseDown[1] = false;
    });

    CBase::GetBase()->GetObserver()->RegisterFunc(CBase::eBASEEVENT::eStartGuiPass, [&](void*) {

        // Measuring frame time
        std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
        std::chrono::duration<float> duration = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - m_frameStartTime);
        m_frameStartTime = currentTime;

        this->SetFrameTime(duration.count());

        ImGui::NewFrame();

        for (auto& it: m_guiModules) it();

//        bool test = true;
//        ImGui::ShowTestWindow(&test);

        ImGui::Render();

        RenderDrawLists(ImGui::GetDrawData());
    });
}

//---------------------------------------------------------------
CImGui::~CImGui() {
    glDeleteBuffers(1, &m_ElementsHandle);
    glDeleteBuffers(1, &m_VertexHandle);
    glDeleteTextures(1, &m_FontTexture);
}

//---------------------------------------------------------------
void CImGui::createFontsTexture() {
    ImGuiIO& io = ImGui::GetIO();

    // Build texture atlas
    unsigned char* pixels;
    int width, height;
    // Load as RGBA 32-bits for OpenGL3 demo because it is more likely to be compatible with user's existing shader.
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

    // Create OpenGL texture
    glGenTextures(1, &m_FontTexture);
    glBindTexture(GL_TEXTURE_2D, m_FontTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    // Store our identifier
    io.Fonts->TexID = (void *)(intptr_t)m_FontTexture;

    // Cleanup (don't clear the input data if you want to append new fonts later)
    io.Fonts->ClearInputData();
    io.Fonts->ClearTexData();
}

//---------------------------------------------------------------
void CImGui::RenderDrawLists(ImDrawData* pDraw_data_) {

    SPtr<CShader> ptrShader = CBase::GetBase()->GetShader();
    if (!ptrShader)
        return;

    const TShaderProgram&       shaderId   = ptrShader->GetProgram("interface");
    const TShaderPropsLocation& properties = ptrShader->GetProperties(shaderId);

    glUseProgram(shaderId);

    // Handle cases of screen coordinates != from framebuffer coordinates (e.g. retina displays)
    ImGuiIO& io = ImGui::GetIO();
    float fb_height = io.DisplaySize.y * io.DisplayFramebufferScale.y;
    pDraw_data_->ScaleClipRects(io.DisplayFramebufferScale);

    glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);

    uint w, h; CBase::GetBase()->GetWndManager()->GetResolution(w, h);

    SPtr<CCamera> ptrCamera = CBase::GetBase()->GetCamera();

    ptrCamera->GetMemento()->PushState();

    ptrCamera->SetViewVolume(0.0, (double)w, (double)h, 0.0, -1.0, 1.0);
    ptrCamera->SetProjectionType(eOrtho);

    auto itPrj = properties.find(eProjectionMatr);
    glUniformMatrix4fv(itPrj->second.location, 1, GL_FALSE, &ptrCamera->GetProjectionMat()[0][0]);

    // Backup GL state
    GLint last_program;
    glGetIntegerv(GL_CURRENT_PROGRAM, &last_program);
    GLint last_texture;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
    GLint last_array_buffer;
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &last_array_buffer);
    GLint last_element_array_buffer;
    glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &last_element_array_buffer);
    GLint last_vertex_array;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &last_vertex_array);
    //GLint last_blend_src;
    //glGetIntegerv(GL_BLEND_SRC, &last_blend_src);
    //GLint last_blend_dst;
    //glGetIntegerv(GL_BLEND_DST, &last_blend_dst);
    //GLint last_blend_equation_rgb;
    //glGetIntegerv(GL_BLEND_EQUATION_RGB, &last_blend_equation_rgb);
    //GLint last_blend_equation_alpha;
    //glGetIntegerv(GL_BLEND_EQUATION_ALPHA, &last_blend_equation_alpha);
    GLint last_viewport[4];
    glGetIntegerv(GL_VIEWPORT, last_viewport);
    GLboolean last_enable_blend         = glIsEnabled(GL_BLEND);
    GLboolean last_enable_cull_face     = glIsEnabled(GL_CULL_FACE);
    GLboolean last_enable_depth_test    = glIsEnabled(GL_DEPTH_TEST);
    GLboolean last_enable_scissor_test  = glIsEnabled(GL_SCISSOR_TEST);

    // Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_SCISSOR_TEST);

    glActiveTexture(GL_TEXTURE0);
    int ret = glGetUniformLocation(shaderId, "texture0");
    glUniform1i(ret, 0);

    for (int n = 0; n < pDraw_data_->CmdListsCount; n++)
    {
        const ImDrawList* cmd_list = pDraw_data_->CmdLists[n];
        const ImDrawIdx* idx_buffer_offset = 0;

        glEnableVertexAttribArray(eVertCoord);
        glEnableVertexAttribArray(eVertTexCoord);
        glEnableVertexAttribArray(eVertColor);

        glBindBuffer(GL_ARRAY_BUFFER, m_VertexHandle);
        glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)cmd_list->VtxBuffer.size() * sizeof(ImDrawVert), (GLvoid*)&cmd_list->VtxBuffer.front(), GL_STREAM_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementsHandle);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)cmd_list->IdxBuffer.size() * sizeof(ImDrawIdx), (GLvoid*)&cmd_list->IdxBuffer.front(), GL_STREAM_DRAW);

        #define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
            glVertexAttribPointer(eVertCoord, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, pos));
            glVertexAttribPointer(eVertTexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, uv));
            glVertexAttribPointer(eVertColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, col));
        #undef OFFSETOF

        for (const ImDrawCmd* pcmd = cmd_list->CmdBuffer.begin(); pcmd != cmd_list->CmdBuffer.end(); pcmd++)
        {
            if (pcmd->UserCallback)
            {
                pcmd->UserCallback(cmd_list, pcmd);
            }
            else
            {
                glBindTexture(GL_TEXTURE_2D, (GLuint)(intptr_t)pcmd->TextureId);
                glScissor((int)pcmd->ClipRect.x, (int)(fb_height - pcmd->ClipRect.w), (int)(pcmd->ClipRect.z - pcmd->ClipRect.x), (int)(pcmd->ClipRect.w - pcmd->ClipRect.y));
                glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, GL_UNSIGNED_SHORT, idx_buffer_offset);
            }
            idx_buffer_offset += pcmd->ElemCount;
        }
    }

    // Restore modified GL state
    glUseProgram(last_program);
    glBindTexture(GL_TEXTURE_2D, last_texture);
    glBindBuffer(GL_ARRAY_BUFFER, last_array_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, last_element_array_buffer);
    glBindVertexArray(last_vertex_array);
    //glBlendEquationSeparate(last_blend_equation_rgb, last_blend_equation_alpha);
    //glBlendFunc(last_blend_src, last_blend_dst);
    if (last_enable_blend) glEnable(GL_BLEND); else glDisable(GL_BLEND);
    if (last_enable_cull_face) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
    if (last_enable_depth_test) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
    if (last_enable_scissor_test) glEnable(GL_SCISSOR_TEST); else glDisable(GL_SCISSOR_TEST);

    CBase::GetBase()->GetObserver()->SignalFunc(CBase::eBASEEVENT::eGuiPass, nullptr);

    glViewport(last_viewport[0], last_viewport[1], (GLsizei)last_viewport[2], (GLsizei)last_viewport[3]);

    ptrCamera->GetMemento()->PopState();
}

//---------------------------------------------------------------
void CImGui::SetViewport(int width_, int height_) {

    ImGuiIO& io = ImGui::GetIO();

    io.DisplaySize = ImVec2((float)width_, (float)height_);
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
}

//---------------------------------------------------------------
void CImGui::SetFrameTime(float val_) {

    ImGuiIO& io = ImGui::GetIO();

    io.DeltaTime = val_;
}

//---------------------------------------------------------------
void CImGui::AddGuiModule(std::function<void()> func_) {
    m_guiModules.push_back(func_);
}
