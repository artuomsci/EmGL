#ifndef CIMGUI_H
#define CIMGUI_H

#include <functional>
#include <vector>

#include <GL/glew.h>

#include "imgui-master/imgui.h"

namespace agl {

class CImGui
{
public:

    CImGui();
    ~CImGui();

    void RenderDrawLists(ImDrawData* pDraw_data_);
    void SetViewport(int width_, int height_);
    void SetFrameTime(float val_);

    void AddGuiModule(std::function<void()> func_);

private:

    void createFontsTexture();
    void handleKeyUp(unsigned long keycode_);
    void handleKeyDown(unsigned long keycode_);

    GLuint m_FontTexture;
    GLuint m_ElementsHandle, m_VertexHandle;

    std::vector<std::function<void()>>          m_guiModules;

    std::chrono::time_point<std::chrono::system_clock> m_frameStartTime;
};

}

#endif // CIMGUI_H
