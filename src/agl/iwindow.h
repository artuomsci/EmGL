#ifndef IWINDOW
#define IWINDOW

#include <functional>

#include "basicdefs.h"

namespace agl {

    typedef std::function<void()> TEmptyFunc;

    class IWindow {
    public:

        virtual ~IWindow() {}
        virtual bool CreateWindow(uint width_, uint height_, uint numSamples_, bool fullScr_) = 0;
        virtual void ResizeWindow(uint width_, uint height_) = 0;
        virtual void GetWindowSize(uint& width_, uint& height_) = 0;
        virtual void Close() = 0;

        virtual void LoopCallback(const TEmptyFunc& loop_) = 0;
        virtual void ResizeWindowCallback(const TEmptyFunc& func_) = 0;
    };
}

#endif // IWINDOW

