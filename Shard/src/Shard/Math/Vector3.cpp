#include "Vector3.h"
#include <cmath>
#include "Conversions.h"
#include "Vector2.h"

namespace Shard::Math
{
    const Vector3 Vector3::zero = { 0, 0, 0 };
    const Vector3 Vector3::one = { 1, 1, 1 };
    const Vector3 Vector3::right = { 1, 0, 0 };
    const Vector3 Vector3::left = { -1, 0, 0 };
    const Vector3 Vector3::up = { 0, 1, 0 };
    const Vector3 Vector3::down = { 0, -1, 0 };
    const Vector3 Vector3::back = { 0, 0, -1 };
    const Vector3 Vector3::forward = { 0, 0, 1 };

    Vector3::Vector3()
        : x(0)
        , y(0)
        , z(0)
    {}

    Vector3::Vector3(float _x, float _y, float _z)
        : x(_x)
        , y(_y)
        , z(_z)
    {}

    Vector3::Vector3(const glm::vec3& _other)
        : x(_other.x)
        , y(_other.y)
        , z(_other.z)
    {}

    Vector3::Vector3(const Vector2& _other, float _z)
        : x(_other.x)
        , y(_other.y)
        , z(_z)
    {}

    Vector3 Vector3::operator+(const Vector3& _other) const
    {
        return { x + _other.x, y + _other.y, z + _other.z };
    }

    Vector3 Vector3::operator-(const Vector3& _other) const
    {
        return { x - _other.x, y - _other.y, z - _other.z };
    }

    Vector3 Vector3::operator*(float _float) const
    {
        return { x * _float, y * _float, z * _float };
    }

    Vector3 Vector3::operator/(float _float) const
    {
        return { x / _float, y / _float, z / _float };
    }

    Vector3 Vector3::Abs() const
    {
        return { std::abs(x), std::abs(y), std::abs(z)};
    }

    float Vector3::Magnitude() const
    {
        return std::sqrt(std::powf(x, 2) + std::powf(y, 2) + std::powf(z, 2));
    }

    Vector3 Vector3::Normalized() const
    {
        float mag = Magnitude();
        return { x / mag, y / mag, z / mag };
    }

    void Vector3::Normalize()
    {
        *this = this->Normalized();
    }

    glm::vec3 Vector3::ToGlm() const
    {
        return glm::vec3(x, y, z);
    }

    float Vector3::Dot(const Vector3& _a, const Vector3& _b)
    {
        return _a.x * _b.x + _a.y * _b.y + _a.z * _b.z;
    }

    float Vector3::Distance(const Vector3& _a, const Vector3& _b)
    {
        return std::sqrtf(std::powf(_a.x - _b.x, 2) + std::powf(_a.y - _b.y, 2) + std::powf(_a.z - _b.z, 2));
    }
}