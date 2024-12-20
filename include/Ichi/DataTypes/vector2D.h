#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <cmath>
namespace ichi::datatypes
{
    class Vector2D
    {
    public:
        Vector2D(float x = 0, float y = 0) : X(x), Y(y) {};

        float getX() const { return X; }
        float getY() const { return Y; }

        void setY(float y) { Y = y; }
        void setX(float x) { X = x; }

        float magnitude() const { return std::sqrt(X * X + Y * Y); }
        Vector2D normalize() const
        {
            float mag = magnitude();
            return (mag != 0) ? Vector2D(X / mag, Y / mag) : Vector2D(0, 0);
        }

        Vector2D &operator+=(const Vector2D &rhs)
        {
            X += rhs.X;
            Y += rhs.Y;
            return *this; // return the result by reference
        }

        friend Vector2D operator+(Vector2D lhs, const Vector2D &rhs)
        {
            lhs += rhs;
            return lhs;
        }

        Vector2D &operator-=(const Vector2D &rhs)
        {
            X -= rhs.X;
            Y -= rhs.Y;
            return *this; // return the result by reference
        }

        bool operator==(const Vector2D &rhs) const
        {
            return X == rhs.getX() && Y == rhs.getY();
        }

        friend Vector2D operator-(Vector2D lhs, const Vector2D &rhs)
        {
            lhs -= rhs;
            return lhs;
        }

        Vector2D operator/(float scaler) const { return (scaler != 0) ? Vector2D(X / scaler, Y / scaler) : Vector2D(0, 0); }
        Vector2D operator*(float scaler) const { return Vector2D(X * scaler, Y * scaler); } // Scalar multiplication

        float operator*(const Vector2D &v2) const { return X * v2.X + Y * v2.Y; } // Dot product
    private:
        float X, Y;
    };
}
#endif