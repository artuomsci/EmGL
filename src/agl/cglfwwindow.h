#ifndef CGLFWWINDOW
#define CGLFWWINDOW


#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include "iwindow.h"

namespace agl {

    class CGLFWwindow : public IWindow {

    public:

        typedef std::function<void()> TEmptyFunc;

        CGLFWwindow();
        ~CGLFWwindow();
        static void         ErrorCallback(int error_, const char* pDescription_);
        static void         KeyCallback(GLFWwindow* pWindow_, int key_, int scancode_, int action_, int mods_);

        virtual void        InitGLEW();
        virtual bool        CreateWindow(uint width_, uint height_, uint numSamples_, bool fullScr_);
        virtual void        ResizeWindow(uint width_, uint height_);
        virtual void        GetWindowSize(uint& width_, uint& height_);
        virtual void        Close();

        virtual void        LoopCallback(const TEmptyFunc& fpLoop_);
        virtual void        ResizeWindowCallback(const TEmptyFunc& fpfunc_);

        static TEmptyFunc   m_fpResizeWndCallback;

        private:

            GLFWwindow*         m_pWindow;
    };
}

#endif // CGLFWWINDOW

