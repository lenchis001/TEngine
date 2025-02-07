#include "Vector3d.h"

namespace TEngine::Components::Graphics::Models
{
    template <class T>
    class Box
    {
    public:
        Box(const Vector3d<T> &position, const Vector3d<T> &size)
            : _topCorner(position + size / (T)2), _bottomCorner(position - size / (T)2)
        {
        }

        bool overlaps(const Box<T> &other) const
        {
            return _topCorner.getX() >= other._bottomCorner.getX() && _bottomCorner.getX() <= other._topCorner.getX() &&
                   _topCorner.getY() >= other._bottomCorner.getY() && _bottomCorner.getY() <= other._topCorner.getY() &&
                   _topCorner.getZ() >= other._bottomCorner.getZ() && _bottomCorner.getZ() <= other._topCorner.getZ();
        }

    private:
        Vector3d<T> _topCorner;
        Vector3d<T> _bottomCorner;
    };

    typedef Box<Vector3d<float>> Box3df;
}