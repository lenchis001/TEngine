#ifndef TENGINE_PARALLELEPIPED_H
#define TENGINE_PARALLELEPIPED_H

#include "Vector3d.h"

namespace TEngine::Components::Graphics::Models
{
    template <class T>
    class Parallelepiped
    {
    public:
        Parallelepiped(
            const Vector3d<T> &bottomCorner,
            const Vector3d<T> &topCorner) : _bottomCorner(bottomCorner),
                                            _topCorner(topCorner) {}

        inline Vector3d<T> getBottomCorner() const { return _bottomCorner; }

        inline Vector3d<T> getTopCorner() const { return _topCorner; }

        inline bool isInside(const Vector3d<T> &point) const
        {
            return point.getX() >= _bottomCorner.getX() &&
                   point.getX() <= _topCorner.getX() &&
                   point.getY() >= _bottomCorner.getY() &&
                   point.getY() <= _topCorner.getY() &&
                   point.getZ() >= _bottomCorner.getZ() &&
                   point.getZ() <= _topCorner.getZ();
        }

        inline bool isInside(const Parallelepiped<T> &parallelepiped) const
        {
            return isInside(parallelepiped.getBottomCorner()) &&
                   isInside(parallelepiped.getTopCorner());
        }

    private:
        Vector3d<T> _bottomCorner;
        Vector3d<T> _topCorner;
    };

    typedef Parallelepiped<float> Parallelepipedf;
}

#endif // TENGINE_PARALLELEPIPED_H