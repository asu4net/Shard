#pragma once
#include "Core.h"
#include <string>
#include "glm.hpp"

namespace Shard::Math
{
    struct Vector2;

    struct SHARD_API Vector3
    {
        float x, y, z;

        static const Vector3 zero;
        static const Vector3 one;
        static const Vector3 right;
        static const Vector3 left;
        static const Vector3 up;
        static const Vector3 down;
        static const Vector3 forward;
        static const Vector3 back;

        Vector3();
        Vector3(float _x, float _y, float _z);
        Vector3(const glm::vec3& _other);
        Vector3(const Vector2& _other, float _z = 0);
        Vector3 operator+(const Vector3& _other) const;
        Vector3 operator-(const Vector3& _other) const;
        Vector3 operator*(float _float) const;
        Vector3 operator/(float _float) const;
        Vector3 Abs() const;
        float Magnitude() const;
        Vector3 Normalized() const;
        void Normalize();
        glm::vec3 ToGlm() const;

        static float Dot(const Vector3& _a, const Vector3& _b);
        static float Distance(const Vector3& _a, const Vector3& _b);
    };
}
