#include "Vec2.h"
#include <cmath>

Vec2::Vec2()
{
}

Vec2::Vec2(float xin, float yin)
    : x(xin), y(yin)
{
}

bool Vec2::operator==(const Vec2& rhs) const
{
    return (x == rhs.x && y == rhs.y);
}

bool Vec2::operator!=(const Vec2& rhs) const
{
    return false;
}

Vec2 Vec2::operator+(const Vec2& rhs) const
{
    return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2& rhs) const
{
    return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator/(const float val) const
{
    return Vec2(x/val, y/val);
}

Vec2 Vec2::operator*(const float val) const
{
    return Vec2(x*val, y*val);
}

void Vec2::operator+=(const Vec2& rhs)
{
    x += rhs.x;
    y += rhs.y;
}

void Vec2::operator-=(const Vec2& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
}

void Vec2::operator*=(const float val)
{
    x *= val;
    y *= val;
}

void Vec2::operator/=(const float val)
{
    x /= val;
    y /= val;
}

float Vec2::dist(const Vec2& rhs) const
{
    return 0.0f;
}

float Vec2::length(const Vec2 p1, const Vec2 p2) const
{
    return 0.0;
}