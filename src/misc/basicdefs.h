#ifndef BASICDEFS_H
#define BASICDEFS_H

#include <memory>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_CXX14
#define GLM_FORCE_PURE
#define GLM_FORCE_INLINE

#include <glm/gtc/quaternion.hpp>

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

#include "glm/mat4x4.hpp"

template <typename T>
using SPtr = std::shared_ptr<T>;

typedef glm::vec4 aVec4;
typedef glm::vec3 aVec3;
typedef glm::vec2 aVec2;

typedef glm::mat3 aMat3;
typedef glm::mat4 aMat4;

typedef glm::tquat<float> aQuat;

typedef unsigned int uint;

typedef long nodeId;

template <typename T>
struct SRectangl {
    T x0, y0, x1, y1;
    SRectangl() : x0(T(0)), y0(T(0)), x1(T(1)), y1(T(1)) {}
    SRectangl(T x0_, T y0_, T x1_, T y1_) : x0(x0_), y0(y0_), x1(x1_), y1(y1_) {}
    };

template <typename T>
class CRect {
public:
    CRect() : x0(T(0)), y0(T(0)), x1(T(1)), y1(T(1)), width(T(1)), height(T(1)), wratio(T(1)) {}
    CRect(T x0_, T y0_, T x1_, T y1_) : x0(x0_), y0(y0_), x1(x1_), y1(y1_) {
        width  = x1 - x0;
        height = y1 - y0;
        wratio = width / height;
    }
    T GetWidth() const { return width; }
    T GetHeight() const { return height; }
    T GetRatio() const {return wratio; }
    void Get(T& x0_, T& y0_, T& x1_, T& y1_) const {
        x0_ = x0; y0_ = y0; x1_ = x1; y1_ = y1;
    }
    void Set(T x0_, T y0_, T x1_, T y1_) {
            x0 = x0_;
            y0 = y0_;
            x1 = x1_;
            y1 = y1_;
            width   = x1 - x0;
            height  = y1 - y0;
            wratio = width / height;
         }
    void Set_P0(T x0_, T y0_) {
            x0 = x0_;
            y0 = y0_;
            width   = x1 - x0;
            height  = y1 - y0;
            wratio = width / height;
         }
    void Set_P1(T x1_, T y1_) {
            x1 = x1_;
            y1 = y1_;
            width   = x1 - x0;
            height  = y1 - y0;
            wratio = width / height;
         }
    bool IsInside(T x_, T y_) const {
        return (x_ > x0) && (x_ < x1) && (y_ > y0) && (y_ < y1) ? true : false;
    }

private:
    T x0, y0, x1, y1, width, height, wratio;
};

typedef CRect<uint> SViewport;





#endif
