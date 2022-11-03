#pragma once
#include <string>
#include "glm.hpp"

namespace Shard::Math
{
    struct Vector3;

    struct Vector2
    {
        float x, y;

        static const Vector2 zero;
        static const Vector2 one;
        static const Vector2 right;
        static const Vector2 left;
        static const Vector2 up;
        static const Vector2 down;

        Vector2();
        Vector2(float _x, float _y);
        Vector2(const glm::vec2& _other);
        Vector2(const Vector3& _other);
        Vector2 operator+(const Vector2& _other) const;
        Vector2 operator-(const Vector2& _other) const;
        Vector2 operator*(float _float) const;
        Vector2 operator/(float _float) const;
        Vector2 Abs() const;
        float Magnitude() const;
        Vector2 Normalized() const;
        void Normalize();
        glm::vec2 ToGlm() const;

        static Vector2 RotateAround(const Vector2& _Center, const Vector2& _Point, float _Angle);
        static float Dot(const Vector2& _a, const Vector2& _b);
        static float Distance(const Vector2& _a, const Vector2& _b);
        static float Angle(const Vector2& _a, const Vector2& _b);
    };
}
