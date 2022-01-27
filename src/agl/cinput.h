#ifndef CINPUT_H
#define CINPUT_H

#ifdef _WEB
#include <emscripten/html5.h>
#endif

#include "cobserver.hpp"
#include "classutils.h"

namespace agl {

class CInput {

    NO_COPY_CLASS(CInput)

    public:

        enum eInputEvents {

            // Keyboard
            eKeyDown,
            eKeyUp,
            eKeyPress,

            // Mouse
            eMouseDown,
            eMouseUp,
            eMouseClick,
            eMouseDoubleClick,
            eMouseMove,
            eMouseWheelUp,
            eMouseWheelDown,
        };

        struct SKeyEvents {
            unsigned long charCode;
            unsigned long keyCode;

            SKeyEvents() :
                charCode(0),
                keyCode(0) {}
            };

        struct SMouseEvents {
                int xPos, yPos;
                // Bitmask for buttons pressed
                unsigned short buttons;

                SMouseEvents() :
                    xPos(0),
                    yPos(0) {}
            };

        CInput();

        static void HookUp();
        static const SMouseEvents& GetLastMouseState();

        static bu::CObserver<eInputEvents> events;

    private:

#ifdef _WEB
        static EM_BOOL mouse_callback(int eventType, const EmscriptenMouseEvent *e, void *userData);
        static EM_BOOL wheel_callback(int eventType, const EmscriptenWheelEvent *e, void *userData);
        static EM_BOOL keyboard_callback(int eventType, const EmscriptenKeyboardEvent *e, void *userData);
#endif

        static SMouseEvents  mouseEvents;
        static SKeyEvents    keyEvents;
    };
}

#endif
