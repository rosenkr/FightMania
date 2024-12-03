#ifndef POINT_H
#define POINT_H

namespace ichi::datatypes
{
    class Point
    {
    public:
        Point(int x = 0, int y = 0) : X(x), Y(y) {}
        int X, Y;

        /* Overloaded operators */
    };
}
#endif