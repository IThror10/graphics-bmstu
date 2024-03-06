#ifndef SPACECOORDS_H
#define SPACECOORDS_H

struct SpaceCoords
{
    SpaceCoords()
    {
        this->x = 0;
        this->y = 0;
        this->z = 0;
        this->empty = 1;
    }

    SpaceCoords(float _x, float _y, float _z)
    {
        this->x = _x;
        this->y = _y;
        this->z = _z;
        this->empty = 1;
    }

    float x;
    float y;
    float z;
    float empty;
};

float len(const SpaceCoords& coords);
float distance(const SpaceCoords& first, const SpaceCoords& second);
void move_point(SpaceCoords& point, const SpaceCoords& move);

float scalar_mult(const SpaceCoords& vectA, const SpaceCoords& vectB);
SpaceCoords find_normal(const SpaceCoords& begin, const SpaceCoords& end);
SpaceCoords vect_mult(const SpaceCoords& vectA, const SpaceCoords& vectB);
SpaceCoords find_normal(const SpaceCoords& pntA, const SpaceCoords& pntB,\
                        const SpaceCoords& pntC, const SpaceCoords& begin);
#endif // SPACECOORDS_H
