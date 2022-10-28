#include "Vector2.h"
#include <cmath>
#include "Conversions.h"

namespace Shard::Math
{
    const Vector2 Vector2::zero = { 0, 0 };
    const Vector2 Vector2::one = { 1, 1 };
    const Vector2 Vector2::right = { 1, 0 };
    const Vector2 Vector2::left = { -1, 0 };
    const Vector2 Vector2::up = { 0, 1 };
    const Vector2 Vector2::down = { 0, -1 };

    Vector2::Vector2()
        : x(0)
        , y(0)
    {}

    Vector2::Vector2(float _x, float _y)
        : x(_x)
        , y(_y)
    {}

    Vector2 Vector2::operator+(const Vector2& _other) const
    {
        return { x + _other.x, y + _other.y };
    }

    Vector2 Vector2::operator-(const Vector2& _other) const
    {
        return { x - _other.x, y - _other.y };
    }

    Vector2 Vector2::operator*(float _float) const
    {
        return { x * _float, y * _float};
    }

    Vector2 Vector2::operator/(float _float) const
    {
        return { x / _float, y / _float };
    }

    Vector2 Vector2::Abs() const
    {
        return { std::abs(x), std::abs(y) };
    }

    float Vector2::Magnitude() const
    {
        return std::sqrt(std::powf(x, 2) + std::powf(y, 2));
    }

    Vector2 Vector2::Normalized() const
    {
        float mag = Magnitude();
        return { x/mag, y/mag };
    }

    void Vector2::Normalize()
    {
        *this = this->Normalized();
    }

    float Vector2::Dot(const Vector2& _a, const Vector2& _b)
    {
        return _a.x * _b.x + _a.y * _b.y;
    }

    float Vector2::Distance(const Vector2& _a, const Vector2& _b)
    {
        return std::sqrtf(std::powf(_a.x - _b.x, 2) + std::powf(_a.y - _b.y, 2));
    }

    float Vector2::Angle(const Vector2& _a, const Vector2& _b)
    {
        float cosAngle = Dot(_a, _b) / (_a.Magnitude() * _b.Magnitude());
        return std::acosf(cosAngle);
    }

    std::string Vector2::ToString() const
    {
        return "(" + StringFromNumber(x) + ", " + StringFromNumber(y) + ")";
    }
}