#ifndef TENGINE_VECTOR3D_H
#define TENGINE_VECTOR3D_H

#include "math.h"

namespace TEngine::Components::Graphics::Models
{
    #define __Vector3dx _data[0]
    #define __Vector3dy _data[1]
    #define __Vector3dz _data[2]

    template <class T>
    class Vector3d
    {
    public:
        Vector3d(T x, T y, T z) {
            __Vector3dx = x;
            __Vector3dy = y;
            __Vector3dz = z;
        }

        inline T getX() const { return __Vector3dx; }
        inline void setX(T value) { __Vector3dx = value; }
        inline T getY() const { return __Vector3dy; }
        inline void setY(T value) { __Vector3dy = value; }
        inline T getZ() const { return __Vector3dz; }
        inline void setZ(T value) { __Vector3dz = value; }

        const T* getInternalData() const
        {
            return _data;
        }

        Vector3d<T> operator+(const Vector3d<T> &other) const
        {
            return Vector3d<T>(__Vector3dx + other.__Vector3dx, __Vector3dy + other.__Vector3dy, __Vector3dz + other.__Vector3dz);
        }

        Vector3d<T> operator+(T scalar) const
        {
            return Vector3d<T>(__Vector3dx + scalar, __Vector3dy + scalar, __Vector3dz + scalar);
        }

        Vector3d<T> operator-(const Vector3d<T> &other) const
        {
            return Vector3d<T>(__Vector3dx - other.__Vector3dx, __Vector3dy - other.__Vector3dy, __Vector3dz - other.__Vector3dz);
        }

        Vector3d<T> operator-(T scalar) const
        {
            return Vector3d<T>(__Vector3dx - scalar, __Vector3dy - scalar, __Vector3dz - scalar);
        }

        Vector3d<T> operator*(const Vector3d<T> &other) const
        {
            return Vector3d<T>(__Vector3dx * other.__Vector3dx, __Vector3dy * other.__Vector3dy, __Vector3dz * other.__Vector3dz);
        }

        Vector3d<T> operator*(T scalar) const
        {
            return Vector3d<T>(__Vector3dx * scalar, __Vector3dy * scalar, __Vector3dz * scalar);
        }

        Vector3d<T> operator/(const Vector3d<T> &other) const
        {
            return Vector3d<T>(__Vector3dx / other.__Vector3dx, __Vector3dy / other.__Vector3dy, __Vector3dz / other.__Vector3dz);
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
            T dx = __Vector3dx - other.__Vector3dx;
            T dy = __Vector3dy - other.__Vector3dy;
            T dz = __Vector3dz - other.__Vector3dz;
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