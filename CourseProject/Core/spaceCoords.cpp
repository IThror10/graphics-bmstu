#include "Core/spaceCoords.h"
#include <cmath>

void move_point(SpaceCoords& point, const SpaceCoords& move)
{
    point.x += move.x;
    point.y += move.y;
    point.z += move.z;
}

float len(const SpaceCoords& coords)
{
    float res = pow(coords.x, 2) + pow(coords.y, 2) + pow(coords.z, 2);
    return sqrt(res);
}

#include <QDebug>
SpaceCoords find_normal(const SpaceCoords& pntA, const SpaceCoords& pntB,\
                        const SpaceCoords& pntC, const SpaceCoords& begin)
{
    SpaceCoords v1(pntB.x - pntA.x, pntB.y - pntA.y, pntB.z - pntA.z);
    SpaceCoords v2(pntC.x - pntA.x, pntC.y - pntA.y, pntC.z - pntA.z);
    SpaceCoords side(pntA.x - begin.x, pntA.y - begin.y, pntA.z - begin.z);

    SpaceCoords normal = vect_mult(v1, v2);
    if (scalar_mult(normal, side) < 0)
    {
        normal.x *= -1;
        normal.y *= -1;
        normal.z *= -1;
    }
    return normal;
}

float scalar_mult(const SpaceCoords& vectA, const SpaceCoords& vectB)
{
    float length = len(vectA) * len(vectB);
    if (length)
        length = (vectA.x * vectB.x + vectA.y * vectB.y + vectA.z * vectB.z) / length;
    return  length;
}

SpaceCoords vect_mult(const SpaceCoords& vectA, const SpaceCoords& vectB)
{
    float x = vectA.y * vectB.z - vectA.z * vectB.y;
    float y = -(vectA.x * vectB.z - vectA.z * vectB.x);
    float z = vectA.x * vectB.y - vectA.y * vectB.x;
    return SpaceCoords(x, y, z);
}

SpaceCoords find_normal(const SpaceCoords& begin, const SpaceCoords& end)
{
    SpaceCoords vector(begin.x - end.x, begin.y - end.y, begin.z - end.z);
    SpaceCoords res;
    if (vector.x)
        res = SpaceCoords(-(vector.y + vector.z) / vector.x, 1, 1);
    else if (vector.y)
        res = SpaceCoords(1, -vector.z / vector.y, 1);
    else
        res = SpaceCoords(1, 1, 0);

    float k = len(res);
    res.x /= k;
    res.y /= k;
    res.z /= k;
    return res;
}

float distance(const SpaceCoords& first, const SpaceCoords& second)
{
    SpaceCoords vect(first.x - second.x, first.y - second.y, first.z - second.z);
    return len(vect);
}
