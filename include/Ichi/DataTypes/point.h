#ifndef POINT_H
#define POINT_H

#include <cmath>

namespace ichi::datatypes
{
    class Point
    {
    public:
        Point(int x = 0, int y = 0) : X(x), Y(y) {}
        int X, Y;

        float distanceTo(const Point &other) const
        {
            int dx = other.X - X;
            int dy = other.Y - Y;

            return std::sqrt(dx * dx + dy * dy);
        }

        bool operator==(const Point &other) const { return other.X == X && other.Y == Y; }
        bool operator!=(const Point &other) const { return !(other == *this); }
        bool operator<(const Point &other) const
        {
            if (this->Y != other.Y)
                return this->Y < other.Y;
            return this->X < other.X;
        }
        Point &operator+=(const Point &rhs)
        {
            X += rhs.X;
            Y += rhs.Y;
            return *this;
        }

        friend Point operator+(Point lhs, const Point &rhs)
        {
            lhs += rhs;
            return lhs;
        }
        Point &operator-=(const Point &rhs)
        {
            X -= rhs.X;
            Y -= rhs.Y;
            return *this;
        }

        friend Point operator-(Point lhs, const Point &rhs)
        {
            lhs -= rhs;
            return lhs;
        }

        /* Overloaded operators */
    };
}
#endif