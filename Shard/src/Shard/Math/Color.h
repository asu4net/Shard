#pragma once
#include "Core.h"
#include "glm.hpp"
#include "Object.h"

namespace Shard::Math
{
    struct SHARD_API Color : public Object
    {
        float r, g, b, a;

        static const Color black;
        static const Color blue;
        static const Color lightBlue;
        static const Color clear;
        static const Color cyan;
        static const Color gray;
        static const Color darkGray;
        static const Color green;
        static const Color lightGreen;
        static const Color grey;
        static const Color darkGrey;
        static const Color magenta;
        static const Color red;
        static const Color lightRed;
        static const Color white;
        static const Color yellow;

        Color();
        Color(float _r, float _g, float _b, float _a = 1);
        Color(const Color& _other);
        Color(const glm::vec4 _other);

        Color operator+(const Color& _other) const;
        Color operator-(const Color& _other) const;
        Color operator*(float _float) const;
        Color operator/(float _float) const;

        glm::vec4 ToGlm() const;
    };
}
