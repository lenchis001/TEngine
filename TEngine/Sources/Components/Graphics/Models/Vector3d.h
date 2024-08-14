#ifndef TENGINE_VECTOR3D_H
#define TENGINE_VECTOR3D_H

#include "math.h"

namespace TEngine::Components::Graphics::Models
{
    template <class T>
    class Vector3d
    {
    public:
        Vector3d(T x, T y, T z) : _x(x), _y(y), _z(z) {}

        inline T getX() const { return _x; }
        inline T getY() const { return _y; }
        inline T getZ() const { return _z; }

        Vector3d<T> operator+(const Vector3d<T> &other) const
        {
            return Vector3d<T>(_x + other._x, _y + other._y, _z + other._z);
        }

        Vector3d<T> operator-(const Vector3d<T> &other) const
        {
            return Vector3d<T>(_x - other._x, _y - other._y, _z - other._z);
        }

        Vector3d<T> operator*(const Vector3d<T> &other) const
        {
            return Vector3d<T>(_x * other._x, _y * other._y, _z * other._z);
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

        Vector3d<T> getNormalized() const
        {
            T length = std::sqrt(getX() * getX() + getY() * getY() + getZ() * getZ());

            return Vector3d<T>(
                getX() / length,
                getY() / length,
                getZ() / length);
        }

        Vector3d<T> getNegative() const {
            return Vector3d<T>(-getX(), -getY(), -getZ());
        }

    private:
        T _x;
        T _y;
        T _z;
    };

    typedef Vector3d<float> Vector3df;
    typedef Vector3d<double> Vector3dd;
    typedef Vector3d<int> Vector3di;
}

#endif // TENGINE_VECTOR3D_H