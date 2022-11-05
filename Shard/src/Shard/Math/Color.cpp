#include "Color.h"

namespace Shard::Math
{
    const Color Color::Black = { 0, 0, 0, 1 };
    const Color Color::Blue = { 0, 0, 1, 1 };
    const Color Color::LightBlue = { .3f, .3f, 1, 1 };
    const Color Color::Clear = { 0, 0, 0, 0 };
    const Color Color::Cyan = { 0, 1, 1, 1 };
    const Color Color::Gray = { .5f, .5f, .5f, 1 };
    const Color Color::DarkGray = { .2f, .2f, .2f, 1 };
    const Color Color::Green = { 0, 1, 0, 1 };
    const Color Color::LightGreen = { .3f, 1, .3f, 1 };
    const Color Color::Grey = { .5f, .5f, .5f, 1 };
    const Color Color::DarkGrey = { .8f, .8f, .8f, 1 };
    const Color Color::Magenta = { 1, 0, 1, 1 };
    const Color Color::Red = { 1, 0, 0, 1 };
    const Color Color::LightRed = { 1, .3f, .3f, 1 };
    const Color Color::White = { 1, 1, 1, 1 };
    const Color Color::Yellow = { 1, .92f, .016f, 1 }; //From Unity: the color is nice to look at!

    Color::Color()
        : r(0)
        , g(0)
        , b(0)
        , a(1)
    {}

    Color::Color(float _r, float _g, float _b, float _a)
        : r(_r)
        , g(_g)
        , b(_b)
        , a(_a)
    {}

    Color::Color(const Color & _other)
        : r(_other.r)
        , g(_other.g)
        , b(_other.b)
        , a(_other.a)
    {}

    Color::Color(const glm::vec4 _other)
        : r(_other.r)
        , g(_other.g)
        , b(_other.b)
        , a(_other.a)
    {}

    Color Color::operator+(const Color& _other) const
    {
        return { r + _other.r, g + _other.g, b + _other.b, a + _other.a };
    }

    Color Color::operator-(const Color& _other) const
    {
        return { r - _other.r, g - _other.g, b - _other.b, a - _other.a };
    }

    Color Color::operator*(float _float) const
    {
        return { r * _float, g * _float, b * _float, a * _float };
    }

    Color Color::operator/(float _float) const
    {
        return { r / _float, g / _float, b / _float, a / _float};
    }

    glm::vec4 Color::ToGlm() const
    {
        return glm::vec4(r, g, b, a);
    }
}