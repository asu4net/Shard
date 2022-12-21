#pragma once

namespace Shard
{
    struct Color
    {
        float r, g, b, a;

        static const Color Black;
        static const Color Blue;
        static const Color LightBlue;
        static const Color Clear;
        static const Color Cyan;
        static const Color Gray;
        static const Color DarkGray;
        static const Color Green;
        static const Color LightGreen;
        static const Color Grey;
        static const Color DarkGrey;
        static const Color Magenta;
        static const Color Red;
        static const Color LightRed;
        static const Color White;
        static const Color Yellow;

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
