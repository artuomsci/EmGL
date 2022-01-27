#ifndef CCOLOR_H
#define CCOLOR_H

namespace agl {

//---------------------------------------------------------------
template <typename T>
class CColor {

    public:
        CColor(T r_ = 0, T g_ = 0, T b_ = 0, T a_ = 0);
        T r, g, b, a;
    };

//---------------------------------------------------------------
template <typename T>
CColor<T>::CColor(T r_, T g_, T b_, T a_) :
    r(r_), g(g_), b(b_), a(a_) {
    }
}

#endif
