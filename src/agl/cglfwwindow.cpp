#include <stdio.h>

#include "cglfwwindow.h"

using namespace agl;

CGLFWwindow::TEmptyFunc CGLFWwindow::m_fpResizeWndCallback = nullptr;

//---------------------------------------------------------------
void resizeWndCallback(GLFWwindow* pWindow_, int width_, int height_) {
    if (CGLFWwindow::m_fpResizeWndCallback)
        CGLFWwindow::m_fpResizeWndCallback();
}

//---------------------------------------------------------------
CGLFWwindow::CGLFWwindow()
{

}

//---------------------------------------------------------------
CGLFWwindow::~CGLFWwindow()
{

}

//---------------------------------------------------------------
void CGLFWwindow::InitGLEW() {

        glewExperimental = GL_TRUE;

        GLenum err = glewInit();
        if (GLEW_OK != err){
          printf("Error: %s\n", glewGetErrorString(err));
        }

        printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION) );
}

//---------------------------------------------------------------
void CGLFWwindow::ErrorCallback(int error_, const char* pDescription_) {
    fputs(pDescription_, stderr);
}

//---------------------------------------------------------------
void CGLFWwindow::KeyCallback(GLFWwindow* pWindow_, int key_, int scancode_, int action_, int mods_) {

}

//---------------------------------------------------------------
bool CGLFWwindow::CreateWindow(uint width_, uint height_, uint numSamples_, bool fullScr_) {

    glfwSetErrorCallback(ErrorCallback);

    if (!glfwInit())
        return false;

    GLFWmonitor*        pMonitor    = glfwGetPrimaryMonitor();
    const GLFWvidmode*  pMode       = glfwGetVideoMode(pMonitor);

    glfwWindowHint(GLFW_RED_BITS,       pMode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS,     pMode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS,      pMode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE,   pMode->refreshRate);

//    glfwWindowHint(GLFW_SAMPLES, numSamples_);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

    if (fullScr_)
        m_pWindow = glfwCreateWindow(width_, height_, "MainWnd", NULL, NULL);
    else
        m_pWindow = glfwCreateWindow(width_, height_, "MainWnd", NULL, NULL);

    if (!m_pWindow) {
        glfwTerminate();
        return false;
    }

    typedef void (* GLFWwindowsizefun)(GLFWwindow*,int,int);

    glfwSetWindowSizeCallback(m_pWindow, &resizeWndCallback);

    glfwMakeContextCurrent(m_pWindow);
    glfwSwapInterval(1);
    glfwSetKeyCallback(m_pWindow, KeyCallback);

    InitGLEW();

    return true;
}

//---------------------------------------------------------------
void CGLFWwindow::ResizeWindow(uint width_, uint height_) {
    glfwSetWindowSize(m_pWindow, width_, height_);
}

//---------------------------------------------------------------
void CGLFWwindow::GetWindowSize(uint& width_, uint& height_) {
    glfwGetWindowSize(m_pWindow, (int*)&width_, (int*)&height_);
}

//---------------------------------------------------------------
void CGLFWwindow::LoopCallback(const TEmptyFunc& fpLoop_) {
    while (!glfwWindowShouldClose(m_pWindow)) {
            if (fpLoop_)
                fpLoop_();
            glfwSwapBuffers(m_pWindow);
            glfwPollEvents();
        }
    glfwDestroyWindow(m_pWindow);
    glfwTerminate();
}

//---------------------------------------------------------------
void CGLFWwindow::ResizeWindowCallback(const TEmptyFunc& fpfunc_) {
    CGLFWwindow::m_fpResizeWndCallback = fpfunc_;
}

//---------------------------------------------------------------
void CGLFWwindow::Close() {
}
