#ifndef TENGINE_VECTOR3D_H
#define TENGINE_VECTOR3D_H

#include "math.h"

namespace TEngine::Components::Graphics::Models
{
    #define _x _data[0]
    #define x(v) _data[0] = v
    #define _y _data[1]
    #define y(v) _data[1] = v
    #define _z _data[2]
    #define z(v) _data[2] = v

    template <class T>
    class Vector3d
    {
    public:
        Vector3d(T x, T y, T z) {
            _x = x;
            _y = y;
            _z = z;
        }

        inline T getX() const { return _x; }
        inline void setX(T value) { _x = value; }
        inline T getY() const { return _y; }
        inline void setY(T value) { _y = value; }
        inline T getZ() const { return _z; }
        inline void setZ(T value) { _z = value; }

        const T* getInternalData() const
        {
            return _data;
        }

        Vector3d<T> operator+(const Vector3d<T> &other) const
        {
            return Vector3d<T>(_x + other._x, _y + other._y, _z + other._z);
        }

        Vector3d<T> operator+(T scalar) const
        {
            return Vector3d<T>(_x + scalar, _y + scalar, _z + scalar);
        }

        Vector3d<T> operator-(const Vector3d<T> &other) const
        {
            return Vector3d<T>(_x - other._x, _y - other._y, _z - other._z);
        }

        Vector3d<T> operator-(T scalar) const
        {
            return Vector3d<T>(_x - scalar, _y - scalar, _z - scalar);
        }

        Vector3d<T> operator*(const Vector3d<T> &other) const
        {
            return Vector3d<T>(_x * other._x, _y * other._y, _z * other._z);
        }

        Vector3d<T> operator*(T scalar) const
        {
            return Vector3d<T>(_x * scalar, _y * scalar, _z * scalar);
        }

        Vector3d<T> operator/(const Vector3d<T> &other) const
        {
            return Vector3d<T>(_x / other._x, _y / other._y, _z / other._z);
        }

        Vector3d<T> cross(const Vector3d<T> otherVector) const
        {
            return Vector3d(
                getY() * otherVector.getZ() - getZ() * otherVector.getY(),
                getZ() * otherVector.getX() - getX() * otherVector.getZ(),
                getX() * otherVector.getY() - getY() * otherVector.getX());
        }

        T dot(const Vector3d<T> &other) const
        {
            return getX() * other.getX() + getY() * other.getY() + getZ() * other.getZ();
        }

        Vector3d<T> getNormalized() const
        {
            T length = sqrt(getX() * getX() + getY() * getY() + getZ() * getZ());

            return Vector3d<T>(
                getX() / length,
                getY() / length,
                getZ() / length);
        }

        Vector3d<T> getNegative() const
        {
            return Vector3d<T>(-getX(), -getY(), -getZ());
        }

        T distance(const Vector3d<T> &other) const
        {
            T dx = _x - other._x;
            T dy = _y - other._y;
            T dz = _z - other._z;
            return sqrt(dx * dx + dy * dy + dz * dz);
        }

    private:
        T _data[3];
    };

    typedef Vector3d<float> Vector3df;
    typedef Vector3d<double> Vector3dd;
    typedef Vector3d<int> Vector3di;
}

#endif // TENGINE_VECTOR3D_H