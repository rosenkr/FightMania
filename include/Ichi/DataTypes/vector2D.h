#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <cmath>
namespace ichi
{
    class Vector2D
    {
    public:
        Vector2D(float x = 0, float y = 0) : X(x), Y(y) {};

        float getX() const { return X; }
        float getY() const { return Y; }

        void setY(float y) { Y = y;}

        float magnitude() const { return std::sqrt(X * X + Y * Y); }
        Vector2D normalize() const
        {
            float mag = magnitude();
            return (mag != 0) ? Vector2D(X / mag, Y / mag) : Vector2D(0, 0);
        }

        Vector2D operator+(const Vector2D &v2) const { return Vector2D(X + v2.X, Y + v2.Y); }
        Vector2D operator-(const Vector2D &v2) const { return Vector2D(X - v2.X, Y - v2.Y); }
        Vector2D operator/(float scaler) const { return (scaler != 0) ? Vector2D(X / scaler, Y / scaler) : Vector2D(0, 0); }
        Vector2D operator*(float scaler) const { return Vector2D(X * scaler, Y * scaler); } // Scalar multiplication
        float operator*(const Vector2D &v2) const { return X * v2.X + Y * v2.Y; }           // Dot product
    private:
        float X, Y;
    };
}
#endif