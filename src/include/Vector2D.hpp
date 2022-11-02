#pragma once

#include <iostream>

class Vector2D
{
private:
public:
    float x, y;
    Vector2D();
    Vector2D(float x, float y);

    Vector2D &Add(const Vector2D &vec);
    Vector2D &Substract(const Vector2D &vec);
    Vector2D &Multiply(const Vector2D &vec);
    Vector2D &Divide(const Vector2D &vec);

    friend Vector2D &operator+(Vector2D &v1, const Vector2D &v2);
    friend Vector2D &operator-(Vector2D &v1, const Vector2D &v2);
    friend Vector2D &operator*(Vector2D &v1, const Vector2D &v2);
    friend Vector2D &operator/(Vector2D &v1, const Vector2D &v2);

    Vector2D &operator+=(const Vector2D &vec);
    Vector2D &operator-=(const Vector2D &vec);
    Vector2D &operator*=(const Vector2D &vec);
    Vector2D &operator/=(const Vector2D &vec);

    Vector2D &operator*(const int &k);
    Vector2D &operator*=(const int &k);
    Vector2D &operator*(const float &k);
    Vector2D &operator*=(const float &k);
    Vector2D &Zero();

    friend std::ostream &operator<<(std::ostream &stream, const Vector2D &vec);

    float magnitude();
    Vector2D unit();
    Vector2D perpendicularUnit();
    Vector2D dot(const Vector2D &vec);
};