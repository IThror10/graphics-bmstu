#ifndef FLATCOORDS_H
#define FLATCOORDS_H

class FlatCoords
{
public:
    float x;
    float y;

    FlatCoords();
    FlatCoords(float x, float y);
    FlatCoords(const FlatCoords&);
    FlatCoords& operator=(const FlatCoords&);

    bool operator==(const FlatCoords&)const;
    bool operator!=(const FlatCoords&)const;

    FlatCoords operator+(const FlatCoords&) const;
    FlatCoords operator-(const FlatCoords&) const;
    FlatCoords operator*(float number) const;

    FlatCoords& operator+=(const FlatCoords&);
    FlatCoords& operator-=(const FlatCoords&);
    FlatCoords& operator*=(float number);

    //Methods
    FlatCoords createVector(float newlen) const;
    FlatCoords& rotate(float angle);
    float angle(const FlatCoords& coords) const;
    float distance(const FlatCoords& coords) const;
    FlatCoords normalIntersect(const FlatCoords& p1, const FlatCoords& p2) const;
    FlatCoords normal(const FlatCoords& endPnt) const;
    float len() const;
};
#endif // FLATCOORDS_H
