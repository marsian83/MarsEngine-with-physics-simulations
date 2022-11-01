#include "Vector2D.hpp"

Vector2D::Vector2D() : x(0), y(0) {}

Vector2D::Vector2D(float x_in, float y_in) : x(x_in), y(y_in) {}

Vector2D &Vector2D::Add(const Vector2D &vec)
{
    this->x += vec.x;
    this->y += vec.y;

    return *this;
}

Vector2D &Vector2D::Substract(const Vector2D &vec)
{
    this->x -= vec.x;
    this->y -= vec.y;

    return *this;
}

Vector2D &Vector2D::Multiply(const Vector2D &vec)
{
    this->x *= vec.x;
    this->y *= vec.y;

    return *this;
}

Vector2D &Vector2D::Divide(const Vector2D &vec)
{
    this->x /= vec.x;
    this->y /= vec.y;

    return *this;
}

Vector2D &operator+(Vector2D &v1, const Vector2D &v2)
{
    return v1.Add(v2);
}
Vector2D &operator-(Vector2D &v1, const Vector2D &v2)
{
    return v1.Substract(v2);
}
Vector2D &operator*(Vector2D &v1, const Vector2D &v2)
{
    return v1.Multiply(v2);
}
Vector2D &operator/(Vector2D &v1, const Vector2D &v2)
{
    return v1.Divide(v2);
}

Vector2D &Vector2D::operator+=(const Vector2D &vec)
{
    return this->Add(vec);
}
Vector2D &Vector2D::operator-=(const Vector2D &vec)
{
    return this->Substract(vec);
}
Vector2D &Vector2D::operator*=(const Vector2D &vec)
{
    return this->Multiply(vec);
}
Vector2D &Vector2D::operator/=(const Vector2D &vec)
{
    return this->Divide(vec);
}

Vector2D &Vector2D::operator*(const int &k)
{
    this->x *= k;
    this->y *= k;

    return *this;
}

Vector2D &Vector2D::operator*=(const int &k)
{
    this->x *= k;
    this->y *= k;

    return *this;
}

Vector2D &Vector2D::operator*(const float &k)
{
    this->x *= k;
    this->y *= k;

    return *this;
}

Vector2D &Vector2D::operator*=(const float &k)
{
    this->x *= k;
    this->y *= k;

    return *this;
}

Vector2D &Vector2D::Zero()
{
    this->x = this->y = 0;

    return *this;
}

std::ostream &operator<<(std::ostream &stream, const Vector2D &vec)
{
    stream << "(" << vec.x << "," << vec.y << ")";
    return stream;
}