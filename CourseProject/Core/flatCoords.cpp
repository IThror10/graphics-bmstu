#include "Core/flatCoords.h"
#include <cmath>

FlatCoords::FlatCoords()
{
    this->x = 0;
    this->y = 0;
}

FlatCoords::FlatCoords(float _x, float _y)
{
    this->x = _x;
    this->y = _y;
}

FlatCoords::FlatCoords(const FlatCoords& given)
{
    this->x = given.x;
    this->y = given.y;
}

FlatCoords& FlatCoords::operator=(const FlatCoords& given)
{
    this->x = given.x;
    this->y = given.y;
    return *this;
}

bool FlatCoords::operator==(const FlatCoords& given) const
{
    return (fabs(this->x - given.x) < 1e-3 && fabs(this->y - given.y) < 1e-3);
}

bool FlatCoords::operator!=(const FlatCoords& given) const
{
    return (fabs(this->x - given.x) >= 1e-3 || fabs(this->y - given.y) >= 1e-3);
}

FlatCoords FlatCoords::operator+(const FlatCoords& given) const
{
    FlatCoords answer = *this;
    answer.x += given.x;
    answer.y += given.y;
    return answer;
}

FlatCoords FlatCoords::operator-(const FlatCoords& given) const
{
    FlatCoords answer = *this;
    answer.x -= given.x;
    answer.y -= given.y;
    return answer;
}

FlatCoords FlatCoords::operator*(float number) const
{
    FlatCoords answer = *this;
    answer.x *= number;
    answer.y *= number;
    return answer;
}

FlatCoords& FlatCoords::operator+=(const FlatCoords& given)
{
    this->x += given.x;
    this->y += given.y;
    return *this;
}

FlatCoords& FlatCoords::operator-=(const FlatCoords& given)
{
    this->x -= given.x;
    this->y -= given.y;
    return *this;
}

FlatCoords& FlatCoords::operator*=(float number)
{
    this->x *= number;
    this->y *= number;
    return *this;
}

FlatCoords FlatCoords::createVector(float newlen) const
{
    FlatCoords answer = *this;
    if (newlen == 0)
    {
        answer.x = 0;
        answer.y = 0;
    }
    else
    {
        float curlen = this->len();
        float k = newlen / curlen;
        answer *= k;
    }
    return answer;
}

FlatCoords& FlatCoords::rotate(float angle)
{
    float rads = angle * M_PI / 180;

    float new_x = this->x * cos(rads) - this->y * sin(rads);
    float new_y = this->x * sin(rads) + this->y * cos(rads);

    this->x = new_x;
    this->y = new_y;
    return *this;
}

float FlatCoords::angle(const FlatCoords& coords) const
{
    float length = this->len() * coords.len(), angle;
    if (length < 1e-6)
        angle = 0;
    else
    {
        float rads = acos((this->x * coords.x + this->y * coords.y) / length);
        angle = rads * 180 / M_PI;
        int direction = (this->x * coords.y - this->y * coords.x < 0 ? -1 : 1);
        if (direction < 0)
            angle = 360 - angle;
    }
    return angle;
}

float FlatCoords::distance(const FlatCoords& coords) const
{
    return sqrt(pow(this->x - coords.x, 2) + pow(this->y - coords.y, 2));
}

float FlatCoords::len() const
{
    return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

FlatCoords FlatCoords::normalIntersect(const FlatCoords& p1, const FlatCoords& p2) const
{
    float xz, yz;
    if (p1.x == p2.x)
    {
        xz = p1.x;
        yz = this->y;
    }
    else if (p1.y == p2.y)
    {
        xz = this->x;
        yz = p1.y;
    }
    else
    {
        float k1 = (p1.y - p2.y) / (p1.x - p2.x), k2 = -1 / k1;
        float b1 = p1.y - k1 * p1.x, b2 = this->y - k2 * this->x;

        xz = (b2 - b1) / (k1 - k2);
        yz = k1 * xz + b1;
    }
    return FlatCoords(xz, yz);
}

FlatCoords FlatCoords::normal(const FlatCoords& endPnt) const
{
    float xz = 0, yz = 0;
    if (this->x == endPnt.x)
        xz = 1;
    else if (this->y == endPnt.y)
        yz = 1;
    else
    {
        float k1 = (this->y - endPnt.y) / (this->x - endPnt.x), k2 = -1 / k1;
        xz += 1;
        yz += k2;
    }
    return FlatCoords(xz, yz);
}
