#ifndef TENGINE_MATRIX4X4_H
#define TENGINE_MATRIX4X4_H

#include <string>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <math.h>
#include <cstring>
#include <stdarg.h>

#include "Vector3d.h"

namespace TEngine::Components::Graphics::Models
{
#define _m(l, c) _data[(c - 1) * 4 + l - 1]

#define _m11 _m(1, 1)
#define _m21 _m(2, 1)
#define _m31 _m(3, 1)
#define _m41 _m(4, 1)

#define _m12 _m(1, 2)
#define _m22 _m(2, 2)
#define _m32 _m(3, 2)
#define _m42 _m(4, 2)

#define _m13 _m(1, 3)
#define _m23 _m(2, 3)
#define _m33 _m(3, 3)
#define _m43 _m(4, 3)

#define _m14 _m(1, 4)
#define _m24 _m(2, 4)
#define _m34 _m(3, 4)
#define _m44 _m(4, 4)

    template <typename T>
    class Matrix4x4
    {
    public:
        Matrix4x4() : Matrix4x4(.0f) {}

        Matrix4x4(const Matrix4x4 &other)
        {
            _data = new T[16];

            std::memcpy(_data, other._data, sizeof(T) * 16);
        };

        Matrix4x4(Matrix4x4 &&other)
        {
            delete[] _data;

            _data = other._data;

            other._data = nullptr;
        }

        Matrix4x4 &operator=(const Matrix4x4 &other)
        {
            if (this->_data != other._data)
            {
                std::memcpy(_data, other._data, sizeof(T) * 16);
            }

            return *this;
        }

        Matrix4x4 &operator=(Matrix4x4 &&other)
        {
            assert(_data != other._data && "Self assignment detected");

            delete[] _data;

            _data = other._data;

            other._data = nullptr;

            return *this;
        }

        ~Matrix4x4()
        {
            if (_data)
            {
                delete[] _data;
            }
        }

        Matrix4x4(T m11, T m12, T m13, T m14,
                  T m21, T m22, T m23, T m24,
                  T m31, T m32, T m33, T m34,
                  T m41, T m42, T m43, T m44)
        {
            _data = new T[16];

            _m11 = m11;
            _m12 = m12;
            _m13 = m13;
            _m14 = m14;
            _m21 = m21;
            _m22 = m22;
            _m23 = m23;
            _m24 = m24;
            _m31 = m31;
            _m32 = m32;
            _m33 = m33;
            _m34 = m34;
            _m41 = m41;
            _m42 = m42;
            _m43 = m43;
            _m44 = m44;
        }

        Matrix4x4(T value)
        {
            _data = new T[16];

            _m11 = value;
            _m12 = 0;
            _m13 = 0;
            _m14 = 0;
            _m21 = 0;
            _m22 = value;
            _m23 = 0;
            _m24 = 0;
            _m31 = 0;
            _m32 = 0;
            _m33 = value;
            _m34 = 0;
            _m41 = 0;
            _m42 = 0;
            _m43 = 0;
            _m44 = 1;
        }

        Matrix4x4 operator*(const Matrix4x4 &other) const
        {
            return Matrix4x4(
                _m11 * other._m11 + _m12 * other._m21 + _m13 * other._m31 + _m14 * other._m41,
                _m11 * other._m12 + _m12 * other._m22 + _m13 * other._m32 + _m14 * other._m42,
                _m11 * other._m13 + _m12 * other._m23 + _m13 * other._m33 + _m14 * other._m43,
                _m11 * other._m14 + _m12 * other._m24 + _m13 * other._m34 + _m14 * other._m44,

                _m21 * other._m11 + _m22 * other._m21 + _m23 * other._m31 + _m24 * other._m41,
                _m21 * other._m12 + _m22 * other._m22 + _m23 * other._m32 + _m24 * other._m42,
                _m21 * other._m13 + _m22 * other._m23 + _m23 * other._m33 + _m24 * other._m43,
                _m21 * other._m14 + _m22 * other._m24 + _m23 * other._m34 + _m24 * other._m44,

                _m31 * other._m11 + _m32 * other._m21 + _m33 * other._m31 + _m34 * other._m41,
                _m31 * other._m12 + _m32 * other._m22 + _m33 * other._m32 + _m34 * other._m42,
                _m31 * other._m13 + _m32 * other._m23 + _m33 * other._m33 + _m34 * other._m43,
                _m31 * other._m14 + _m32 * other._m24 + _m33 * other._m34 + _m34 * other._m44,

                _m41 * other._m11 + _m42 * other._m21 + _m43 * other._m31 + _m44 * other._m41,
                _m41 * other._m12 + _m42 * other._m22 + _m43 * other._m32 + _m44 * other._m42,
                _m41 * other._m13 + _m42 * other._m23 + _m43 * other._m33 + _m44 * other._m43,
                _m41 * other._m14 + _m42 * other._m24 + _m43 * other._m34 + _m44 * other._m44);
        }

        bool operator==(const Matrix4x4 &other) const
        {
            if (_data == other._data)
            {
                return true;
            }

            return memcmp(_data, other._data, sizeof(T) * 16) == 0;
        }

        bool operator!=(const Matrix4x4 &other) const
        {
            return !(*this == other);
        }

        const T *getInternalData() const
        {
            return _data;
        }

        const Vector3d<T> getPosition() const
        {
            return Vector3d<T>(_m14, _m24, _m34);
        }

        Vector3d<T> getRotation() const
        {
            T x = atan2(_m32, _m33);
            T y = atan2(-_m31, sqrt(_m32 * _m32 + _m33 * _m33));
            T z = atan2(_m21, _m11);

            return Vector3d<T>(x, y, z);
        }

        Vector3d<T> getScale() const
        {
            return Vector3d<T>(
                Vector3d<T>(_m11, _m12, _m13).getLength(),
                Vector3d<T>(_m21, _m22, _m23).getLength(),
                Vector3d<T>(_m31, _m32, _m33).getLength());
        }

        inline void setState(T m11, T m12, T m13, T m14,
                             T m21, T m22, T m23, T m24,
                             T m31, T m32, T m33, T m34,
                             T m41, T m42, T m43, T m44)
        {
            _m11 = m11;
            _m12 = m12;
            _m13 = m13;
            _m14 = m14;
            _m21 = m21;
            _m22 = m22;
            _m23 = m23;
            _m24 = m24;
            _m31 = m31;
            _m32 = m32;
            _m33 = m33;
            _m34 = m34;
            _m41 = m41;
            _m42 = m42;
            _m43 = m43;
            _m44 = m44;
        }

        inline void setMultiplyingResult(const Matrix4x4<T> &m1, const Matrix4x4<T> &m2)
        {
            _m11 = m1._m11 * m2._m11 + m1._m12 * m2._m21 + m1._m13 * m2._m31 + m1._m14 * m2._m41;
            _m12 = m1._m11 * m2._m12 + m1._m12 * m2._m22 + m1._m13 * m2._m32 + m1._m14 * m2._m42;
            _m13 = m1._m11 * m2._m13 + m1._m12 * m2._m23 + m1._m13 * m2._m33 + m1._m14 * m2._m43;
            _m14 = m1._m11 * m2._m14 + m1._m12 * m2._m24 + m1._m13 * m2._m34 + m1._m14 * m2._m44;

            _m21 = m1._m21 * m2._m11 + m1._m22 * m2._m21 + m1._m23 * m2._m31 + m1._m24 * m2._m41;
            _m22 = m1._m21 * m2._m12 + m1._m22 * m2._m22 + m1._m23 * m2._m32 + m1._m24 * m2._m42;
            _m23 = m1._m21 * m2._m13 + m1._m22 * m2._m23 + m1._m23 * m2._m33 + m1._m24 * m2._m43;
            _m24 = m1._m21 * m2._m14 + m1._m22 * m2._m24 + m1._m23 * m2._m34 + m1._m24 * m2._m44;

            _m31 = m1._m31 * m2._m11 + m1._m32 * m2._m21 + m1._m33 * m2._m31 + m1._m34 * m2._m41;
            _m32 = m1._m31 * m2._m12 + m1._m32 * m2._m22 + m1._m33 * m2._m32 + m1._m34 * m2._m42;
            _m33 = m1._m31 * m2._m13 + m1._m32 * m2._m23 + m1._m33 * m2._m33 + m1._m34 * m2._m43;
            _m34 = m1._m31 * m2._m14 + m1._m32 * m2._m24 + m1._m33 * m2._m34 + m1._m34 * m2._m44;

            _m41 = m1._m41 * m2._m11 + m1._m42 * m2._m21 + m1._m43 * m2._m31 + m1._m44 * m2._m41;
            _m42 = m1._m41 * m2._m12 + m1._m42 * m2._m22 + m1._m43 * m2._m32 + m1._m44 * m2._m42;
            _m43 = m1._m41 * m2._m13 + m1._m42 * m2._m23 + m1._m43 * m2._m33 + m1._m44 * m2._m43;
            _m44 = m1._m41 * m2._m14 + m1._m42 * m2._m24 + m1._m43 * m2._m34 + m1._m44 * m2._m44;
        }

        inline void setMultiplyingResult(const Matrix4x4<T> &m1, const Matrix4x4<T> &m2, const Matrix4x4<T> &m3, const Matrix4x4<T> &m4)
        {
            setMultiplyingResult(m1, m2);
            setMultiplyingResult(*this, m3);
            setMultiplyingResult(*this, m4);
        }

        void setScale(const Vector3d<T> &scale)
        {
#ifdef TENGINE_DEBUG
            assert(scale.getX() != 0 && scale.getY() != 0 && scale.getZ() != 0 && "Scale cannot be zero");

            assert(
                _m12 == 0 &&
                _m13 == 0 &&
                _m14 == 0 &&
                _m21 == 0 &&
                _m23 == 0 &&
                _m24 == 0 &&
                _m31 == 0 &&
                _m32 == 0 &&
                _m34 == 0 &&
                _m41 == 0 &&
                _m42 == 0 &&
                _m43 == 0 &&
                _m44 == 1 &&
                "The matrix is not a scale matrix");
#endif

            _m11 = scale.getX();
            _m22 = scale.getY();
            _m33 = scale.getZ();
        }

        void setScale(T x, T y, T z)
        {
#ifdef TENGINE_DEBUG
            assert(x != 0 && y != 0 && z != 0 && "Scale cannot be zero");

            assert(
                _m12 == 0 &&
                _m13 == 0 &&
                _m14 == 0 &&
                _m21 == 0 &&
                _m23 == 0 &&
                _m24 == 0 &&
                _m31 == 0 &&
                _m32 == 0 &&
                _m34 == 0 &&
                _m41 == 0 &&
                _m42 == 0 &&
                _m43 == 0 &&
                _m44 == 1 &&
                "The matrix is not a scale matrix");
#endif

            _m11 = x;
            _m22 = y;
            _m33 = z;
        }

        void setRotation(const Vector3d<T> &rotation)
        {
#ifdef TENGINE_DEBUG
            assert(
                _m14 == 0 &&
                _m24 == 0 &&
                _m34 == 0 &&
                _m41 == 0 &&
                _m42 == 0 &&
                _m43 == 0 &&
                _m44 == 1 &&
                "The matrix is not a rotation matrix");
#endif

            setRotation(rotation.getX(), rotation.getY(), rotation.getZ());
        }

        void setRotation(T x, T y, T z)
        {
#ifdef TENGINE_DEBUG
            assert(
                _m14 == 0 &&
                _m24 == 0 &&
                _m34 == 0 &&
                _m41 == 0 &&
                _m42 == 0 &&
                _m43 == 0 &&
                _m44 == 1 &&
                "The matrix is not a rotation matrix");
#endif

            T cx = cos(x);
            T sx = sin(x);
            T cy = cos(y);
            T sy = sin(y);
            T cz = cos(z);
            T sz = sin(z);

            _m11 = cy * cz;
            _m12 = cy * sz;
            _m13 = -sy;
            // _m14 = 0;

            _m21 = sx * sy * cz - cx * sz;
            _m22 = sx * sy * sz + cx * cz;
            _m23 = sx * cy;
            // _m24 = 0;

            _m31 = cx * sy * cz + sx * sz;
            _m32 = cx * sy * sz - sx * cz;
            _m33 = cx * cy;
            // _m34 = 0;

            // _m41 = 0;
            // _m42 = 0;
            // _m43 = 0;
            // _m44 = 1;

            // we don't need to set these values
            // since we expect to work with rotation/1
            // matrices only
        }

        void setTranslation(const Vector3d<T> &position)
        {
#ifdef TENGINE_DEBUG
            assert(
                _m11 == 1 &&
                _m12 == 0 &&
                _m13 == 0 &&
                _m21 == 0 &&
                _m22 == 1 &&
                _m23 == 0 &&
                _m31 == 0 &&
                _m32 == 0 &&
                _m33 == 1 &&
                _m44 == 1 &&
                "The matrix is not a translation matrix");
#endif

            _m14 = position.getX();
            _m24 = position.getY();
            _m34 = position.getZ();
        }

        void setTranslation(T x, T y, T z)
        {
#ifdef TENGINE_DEBUG
            assert(
                _m11 == 1 &&
                _m12 == 0 &&
                _m13 == 0 &&
                _m21 == 0 &&
                _m22 == 1 &&
                _m23 == 0 &&
                _m31 == 0 &&
                _m32 == 0 &&
                _m33 == 1 &&
                _m44 == 1 &&
                "The matrix is not a translation matrix");
#endif

            _m14 = x;
            _m24 = y;
            _m34 = z;
        }

        void print() const
        {
            // save to string
            std::string str;

            str += std::to_string(_m11) + " " + std::to_string(_m12) + " " + std::to_string(_m13) + " " + std::to_string(_m14) + "\n";
            str += std::to_string(_m21) + " " + std::to_string(_m22) + " " + std::to_string(_m23) + " " + std::to_string(_m24) + "\n";
            str += std::to_string(_m31) + " " + std::to_string(_m32) + " " + std::to_string(_m33) + " " + std::to_string(_m34) + "\n";
            str += std::to_string(_m41) + " " + std::to_string(_m42) + " " + std::to_string(_m43) + " " + std::to_string(_m44) + "\n";

            std::cout << str;
        }

    private:
        T *_data;
    };

    typedef Matrix4x4<float> Matrix4x4f;
}

#endif // TENGINE_MATRIX4X4_H