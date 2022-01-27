#include "cinput.h"
#include <iostream>

using namespace agl;

CInput::SMouseEvents    CInput::mouseEvents;
CInput::SKeyEvents      CInput::keyEvents;

bu::CObserver<CInput::eInputEvents>  CInput::events;

//---------------------------------------------------------------
CInput::CInput() {
    }

//---------------------------------------------------------------
void CInput::HookUp() {

#ifdef _WEB
    /**< Setting keyboard callbacks */
    emscripten_set_keypress_callback(   0, 0, 1, agl::CInput::keyboard_callback);
    emscripten_set_keydown_callback(    0, 0, 1, agl::CInput::keyboard_callback);
    emscripten_set_keyup_callback(      0, 0, 1, agl::CInput::keyboard_callback);

    /**< Setting mouse callbacks */
    emscripten_set_click_callback(      0, 0, 1, agl::CInput::mouse_callback);
    emscripten_set_mousedown_callback(  0, 0, 1, agl::CInput::mouse_callback);
    emscripten_set_mouseup_callback(    0, 0, 1, agl::CInput::mouse_callback);
    emscripten_set_dblclick_callback(   0, 0, 1, agl::CInput::mouse_callback);
    emscripten_set_mousemove_callback(  0, 0, 1, agl::CInput::mouse_callback);
    emscripten_set_wheel_callback(      0, 0, 1, agl::CInput::wheel_callback);
#endif

}

//---------------------------------------------------------------
const CInput::SMouseEvents& CInput::GetLastMouseState() {
    return mouseEvents;
}


#ifdef _WEB

//---------------------------------------------------------------
EM_BOOL CInput::keyboard_callback(int eventType, const EmscriptenKeyboardEvent *e, void *userData) {

        if (eventType == EMSCRIPTEN_EVENT_KEYUP) {
            keyEvents.keyCode = e->keyCode;
            events.SignalFunc(eKeyUp, &keyEvents.keyCode);
        }

        if (eventType == EMSCRIPTEN_EVENT_KEYDOWN) {
            keyEvents.keyCode = e->keyCode;
            events.SignalFunc(eKeyDown, &keyEvents.keyCode);
        }

        if (eventType == EMSCRIPTEN_EVENT_KEYPRESS) {
            if (e) {
                keyEvents.charCode = e->charCode;
                events.SignalFunc(eKeyPress, &keyEvents.charCode);
            }
        }
        return 0;
    }

//---------------------------------------------------------------
EM_BOOL CInput::mouse_callback(int eventType, const EmscriptenMouseEvent *e, void *userData) {
    mouseEvents.xPos = e->canvasX;
    mouseEvents.yPos = e->canvasY;
    mouseEvents.buttons = e->buttons;
    if (e->screenX && e->screenY && e->clientX && e->clientY && e->canvasX && e->canvasY && e->targetX && e->targetY) {
        if (e->buttons) {
                if (eventType == EMSCRIPTEN_EVENT_CLICK)
                    events.SignalFunc(eMouseClick, &CInput::mouseEvents);

                if (eventType == EMSCRIPTEN_EVENT_MOUSEDOWN)
                    events.SignalFunc(eMouseDown, &CInput::mouseEvents);

                if (eventType == EMSCRIPTEN_EVENT_DBLCLICK)
                    events.SignalFunc(eMouseDoubleClick, &CInput::mouseEvents);

                if (eventType == EMSCRIPTEN_EVENT_MOUSEUP)
                    events.SignalFunc(eMouseUp, &CInput::mouseEvents);
            }

            if (eventType == EMSCRIPTEN_EVENT_MOUSEMOVE && (e->movementX != 0 || e->movementY != 0))
                events.SignalFunc(eMouseMove, &CInput::mouseEvents);
        }
    return 0;
    }

//---------------------------------------------------------------
EM_BOOL CInput::wheel_callback(int eventType, const EmscriptenWheelEvent *e, void *userData) {
    if (e->deltaY > 0.f || e->deltaY < 0.f) {
        if (e->deltaY > 0)
            events.SignalFunc(eMouseWheelUp, &CInput::mouseEvents);

        if (e->deltaY < 0)
            events.SignalFunc(eMouseWheelDown, &CInput::mouseEvents);
        }
    return 0;
    }

#endif
