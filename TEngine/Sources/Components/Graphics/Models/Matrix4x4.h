#ifndef TENGINE_MATRIX4X4_H
#define TENGINE_MATRIX4X4_H

#include "Vector3d.h"

namespace TEngine::Components::Graphics::Models
{

    template <typename T>
    class Matrix4x4
    {
    public:
        Matrix4x4() = default;
        Matrix4x4(const Matrix4x4 &other) = default;
        Matrix4x4(Matrix4x4 &&other) = default;
        Matrix4x4 &operator=(const Matrix4x4 &other) = default;
        Matrix4x4 &operator=(Matrix4x4 &&other) = default;
        ~Matrix4x4() = default;

        Matrix4x4(T m11, T m12, T m13, T m14,
                  T m21, T m22, T m23, T m24,
                  T m31, T m32, T m33, T m34,
                  T m41, T m42, T m43, T m44)
            : m11(m11), m12(m12), m13(m13), m14(m14),
              m21(m21), m22(m22), m23(m23), m24(m24),
              m31(m31), m32(m32), m33(m33), m34(m34),
              m41(m41), m42(m42), m43(m43), m44(m44)
        {
        }

    private:
        T m11;
        T m12;
        T m13;
        T m14;
        T m21;
        T m22;
        T m23;
        T m24;
        T m31;
        T m32;
        T m33;
        T m34;
        T m41;
        T m42;
        T m43;
        T m44;
    };

    typedef Matrix4x4<float> Matrix4x4f;
}

#endif // TENGINE_MATRIX4X4_H