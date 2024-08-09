namespace TEngine::Components::Graphics::Models
{
    template <class T>
    class Vector2d
    {
    public:
        Vector2d(T x, T y) : _x(x), _y(y) {}

        T getX() const;
        T getY() const;

        Vector2d<T> operator+(const Vector2d<T> &other) const
        {
            return Vector2d<T>(_x + other._x, _y + other._y);
        }

        Vector2d<T> operator-(const Vector2d<T> &other) const
        {
            return Vector2d<T>(_x - other._x, _y - other._y);
        }

        Vector2d<T> operator*(const Vector2d<T> &other) const
        {
            return Vector2d<T>(_x * other._x, _y * other._y);
        }

        Vector2d<T> operator/(const Vector2d<T> &other) const
        {
            return Vector2d<T>(_x / other._x, _y / other._y);
        }

    private:
        T _x;
        T _y;
    };

    typedef Vector2d<float> Vector2df;
    typedef Vector2d<double> Vector2dd;
    typedef Vector2d<int> Vector2di;
}