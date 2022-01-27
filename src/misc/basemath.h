#ifndef BASEMATH_H
#define BASEMATH_H

#include <math.h>

#include "basicdefs.h"

namespace bu {

//---------------------------------------------------------------------------------
template <typename T>
const T     PI              = T(3.14159265358979323846);
template <typename T>
const T     HALF_PI			= PI<T> * T(0.5);
template <typename T>
const T	    TWO_PI			= PI<T> * T(2.0);
template <typename T>
const T	    DEG2RAD		    = PI<T> / T(180.0);
template <typename T>
const T	    RAD2DEG		    = T(180.0) / PI<T>;

const float     FHALF_PI    = PI<float> * 0.5f;
const float	    FTWO_PI     = PI<float> * 2.0f;
const float	    FDEG2RAD    = PI<float> / 180.0f;
const float	    FRAD2DEG	= 180.0f / PI<float>;

//---------------------------------------------------------------------------------
template <typename T>
T minval(const T val0_, const T val1_) {
    return val0_ < val1_ ? val0_ : val1_;
}

//---------------------------------------------------------------------------------
template <typename T>
bool Equal(T a_, T b_, T relevance_ = T(0.000001)) {
    if (fabs(fabs(a_) - fabs(b_)) > relevance_)
        return false;
    else
        return true;
}

//---------------------------------------------------------------------------------
// Check for point to be near/on line (infinite line!)
template <typename T>
bool IsOnLine(const aVec2& p0_, const aVec2& p1_, const aVec2& pnt_, T tolerance_) {
    return Equal<double>(pnt_.y - p0_.y - (p1_.y - p0_.y) * (pnt_.x - p0_.x) / (p1_.x - p0_.x), T(0), tolerance_);
}

//---------------------------------------------------------------------------------
// Check for point to be near/on section
template <typename T>
bool IsOnSection(const aVec2& p0_, const aVec2& p1_, const aVec2& pnt_, T tolerance_) {
    if (Equal<double>(pnt_.y - p0_.y - (p1_.y - p0_.y) * (pnt_.x - p0_.x) / (p1_.x - p0_.x), T(0), tolerance_)) {
        float l0 = glm::length(p0_ - p1_);
        float l1 = glm::length(pnt_ - p1_);
        float l2 = glm::length(pnt_ - p0_);

        if ((l1 > l0) || (l2 > l0))
            return false;
        else
            return true;
    }
    return false;
}

//---------------------------------------------------------------------------------
//          Here is an example of creating Bezier patch surface (3 x 3 grid)

//aMat3 Gx, Gy;

//Gx[0][0] = 0;
//Gx[0][1] = 1;
//Gx[0][2] = 2;

//Gx[1][0] = -1;
//Gx[1][1] = 1;
//Gx[1][2] = 2;

//Gx[2][0] = 0;
//Gx[2][1] = 1;
//Gx[2][2] = 3;


//Gy[0][0] = 3;
//Gy[0][1] = 5;
//Gy[0][2] = 3;

//Gy[1][0] = 2;
//Gy[1][1] = 2;
//Gy[1][2] = 2;

//Gy[2][0] = 1;
//Gy[2][1] = 2;
//Gy[2][2] = 1;

//for (float dt = 0.0f; dt < 1.0f; dt += 0.04f) {
//    for (float ds = 0.0f; ds < 1.0f; ds += 0.04f) {
//        float x = ComputeBezierPatchPoint<float>(dt, ds, Gx);
//        float y = ComputeBezierPatchPoint<float>(dt, ds, Gy);

//        ..CreatePoint(aVec3(x, y, 0));
//    }
//}

//---------------------------------------------------------------------------------
//                       Here is an example of creating loft patch surface

//--------------- Top edge control points
//    aVec2 p0, p1, p2;
//    p0 = aVec2(-1.0, 0.0);
//    p1 = aVec2( 0.0, 1.0);
//    p2 = aVec2( 1.0, 0.0);

//--------------- Bottom edge control points
//    aVec2 p3, p4, p5;
//    p3 = aVec2(-2.0, 3.3);
//    p4 = aVec2( 0.0, 1.0);
//    p5 = aVec2( 2.0, 1.0);

//    for (float dt = 0; dt < 1.0f; dt += 0.04)
//    {
//        aVec2 pnt0;

//        pnt0.x = QuadraticBezierCurve(dt, p0.x, p1.x, p2.x);
//        pnt0.y = QuadraticBezierCurve(dt, p0.y, p1.y, p2.y);

//        aVec2 pnt1;

//        pnt1.x = QuadraticBezierCurve(dt, p3.x, p4.x, p5.x);
//        pnt1.y = QuadraticBezierCurve(dt, p3.y, p4.y, p5.y);

//        for (float ds = 0; ds < 1.0f; ds += 0.04)
//        {
//            aVec2 sPnt;
//            sPnt.x = Interpolate(ds, pnt0.x, pnt1.x);
//            sPnt.y = Interpolate(ds, pnt0.y, pnt1.y);

//            ..CreatePoint(aVec3(sPnt.x, sPnt.y, 0));
//        }

//    }

//---------------------------------------------------------------------------------
template <typename T>
static T Interpolate(T t_, T p0_, T p1_) {
    return (T(1) - t_) * p0_ + t_ * p1_;
}

//---------------------------------------------------------------------------------
template <typename T>
static T CatmullRom(T u_, T x0_, T x1_, T x2_, T x3_) {
    T u2 = u_ * u_;
    T u3 = u2 * u_;
    return ((T(2) * x1_) +
           (-x0_ + x2_) * u_ +
           (T(2) * x0_ - T(5) * x1_ + T(4) * x2_ - x3_) * u2 +
           (-x0_ + T(3) * x1_ - T(3) * x2_ + x3_) * u3) * T(0.5);
}

//---------------------------------------------------------------------------------
template <typename T>
static T CubicBezierCurve(T t_, T p0_, T p1_, T p2_, T p3_) {
    return  pow((T(1) - t_), T(3)) * p0_ +
            T(3) * pow((T(1) - t_), T(2)) * t_ * p1_ +
            T(3) * (T(1) - t_) * t_ * t_ * p2_ +
            t_ * t_ * t_ * p3_;
}

//---------------------------------------------------------------------------------
template <typename T>
static aVec4 CubicBlend(T t_) {
    return aVec4( pow((T(1) - t_), T(3)),
                  T(3) * pow((T(1) - t_), T(2)) * t_,
                  T(3) * (T(1) - t_) * t_ * t_,
                  t_ * t_ * t_);
}

//---------------------------------------------------------------------------------
template <typename T>
static T QuadraticBezierCurve(T t_, T p0_, T p1_, T p2_) {
    return pow(T(1) - t_, T(2)) * p0_ + T(2) * (T(1) - t_) * t_ * p1_ + t_ * t_ * p2_;
}

//---------------------------------------------------------------------------------
template <typename T>
static aVec3 QuadraticBlend(T t_) {
    return aVec3( pow((T(1) - t_), T(2)), T(2) * (T(1) - t_) * t_, t_ * t_ );
}

//---------------------------------------------------------------------------------
// Computing Bezier patch value at specified position u_ and v_ for control points Gc_
template <typename T>
static T ComputeBezierPatchPoint(T u_, T v_, const aMat3& Gc_) {
    return glm::dot(QuadraticBlend<T>(u_), Gc_ * QuadraticBlend<T>(v_));
}

//---------------------------------------------------------------------------------
// Computing Bezier patch value at specified position u_ and v_ for control points Gc_
template <typename T>
static T ComputeBezierPatchPoint(T u_, T v_, const aMat4& Gc_) {
    return glm::dot(CubicBlend<T>(u_), Gc_ * CubicBlend<T>(v_));
}

//---------------------------------------------------------------------------------
// Get control point at t = 0.5
template <typename T>
static T GetQuadraticBezierMidControlPoint(T p0_, T p2_, T pointOnCurve_) {
    return T(2) * pointOnCurve_ - T(0.5) * p0_ - T(0.5) * p2_;
}

//---------------------------------------------------------------------------------
// Get control point at specified t
template <typename T>
static T GetQuadraticBezierControlPoint(T t_, T p0_, T p2_, T pointOnCurve_) {
    return pointOnCurve_ / (T(2) * t_ * (T(1) - t_)) - p0_ * (T(1) - t_) / (T(2) * t_) - (p2_ * t_) / (T(2) * (T(1) - t_));
}

//---------------------------------------------------------------------------------
// Special type of a variable to store triple values
// Automatic check of maximum and minimum boundaries

template <typename T>
class rangeType {
    public:
        rangeType() : minv(0), maxv(1) {}
        bool Set(T val_) {
            if ((val_ <= maxv)&&(val_ >= minv)) m_value = val_;
            else return false;
            }
        T Get(void) {
            return m_value;
            }

        T maxv, minv;

    private:
        T m_value;
    };

//---------------------------------------------------------------------------------
template <typename T>
static T CalcGauss(T x_, T sigma2_) {
    T coeff = T(1.0) / (T(2.0) * PI<T> * sigma2_);
    T expon = -(x_ * x_) / (T(2.0) * sigma2_);
    return (coeff * exp(expon));
    }

}

#endif
