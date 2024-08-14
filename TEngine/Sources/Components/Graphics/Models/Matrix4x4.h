#ifndef TENGINE_MATRIX4X4_H
#define TENGINE_MATRIX4X4_H

#include "Vector3d.h"

#include "cstring"

namespace TEngine::Components::Graphics::Models
{
    #define _m(l,c, val) _data[(l-1)*4 + c-1] = val
    
    #define _m11(val) _m(1,1, val)
    #define _m21(val) _m(2,1, val)
    #define _m31(val) _m(3,1, val)
    #define _m41(val) _m(4,1, val)

    #define _m12(val) _m(1,2, val)
    #define _m22(val) _m(2,2, val)
    #define _m32(val) _m(3,2, val)
    #define _m42(val) _m(4,2, val)

    #define _m13(val) _m(1,3, val)
    #define _m23(val) _m(2,3, val)
    #define _m33(val) _m(3,3, val)
    #define _m43(val) _m(4,3, val)

    #define _m14(val) _m(1,4, val)
    #define _m24(val) _m(2,4, val)
    #define _m34(val) _m(3,4, val)
    #define _m44(val) _m(4,4, val)

    template <typename T>
    class Matrix4x4
    {
    public:
        Matrix4x4(): Matrix4x4(.0f) {}
        
        Matrix4x4(const Matrix4x4 &other) {
            _data = new T[16];

            std::memcpy(_data, other._data, sizeof(T)*16);
        };
        
        Matrix4x4(Matrix4x4 &&other) {
            _data = other._data;

            other._data = nullptr;
        }
        
        Matrix4x4 &operator=(const Matrix4x4 &other) {
            std::memcpy(_data, other._data, sizeof(T)*16);

            return *this;
        }
        
        Matrix4x4 &operator=(Matrix4x4 &&other) {
            _data = other._data;

            other._data = nullptr;

            return *this;
        }
        
        ~Matrix4x4() {
            if(_data) {
                delete[] _data;
            }
        }

        Matrix4x4(T m11, T m12, T m13, T m14,
                  T m21, T m22, T m23, T m24,
                  T m31, T m32, T m33, T m34,
                  T m41, T m42, T m43, T m44)
        {
            _data = new T[16];

            _m11(m11); _m12(m12); _m13(m13); _m14(m14);
            _m21(m21); _m22(m22); _m23(m23); _m24(m24);
            _m31(m31); _m32(m32); _m33(m33); _m34(m34);
            _m41(m41); _m42(m42); _m43(m43); _m44(m44);
        }

        Matrix4x4(T value)
        {
            _data = new T[16];

            _m11(value); _m12(0); _m13(0); _m14(0);
            _m21(0); _m22(value); _m23(0); _m24(0);
            _m31(0); _m32(0); _m33(value); _m34(0);
            _m41(0); _m42(0); _m43(0); _m44(1);
        }

    private:
        T *_data;
    };

    typedef Matrix4x4<float> Matrix4x4f;
}

#endif // TENGINE_MATRIX4X4_H