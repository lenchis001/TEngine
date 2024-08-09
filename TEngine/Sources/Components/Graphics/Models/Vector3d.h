#ifndef TENGINE_VECTOR3D_H
#define TENGINE_VECTOR3D_H

namespace TEngine::Components::Graphics::Models
{
    template <class T>
    class Vector3d
    {
    public:
        Vector3d(T x, T y, T z) : _x(x), _y(y), _z(z) {}

        T getX() const;
        T getY() const;
        T getZ() const;

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