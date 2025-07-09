#pragma once
#include "math.hpp"


class Color
{
public:
    Color() : m_red(0), m_green(0), m_blue(0) {};

    Color(uint8_t r, uint8_t g, uint8_t b)
        : m_red(r), m_green(g), m_blue(b) {};

    static inline Color White() { return Color(255, 255, 255); }

    Vec3     ToFloats();
    Vec4     ToPaddedFloats();
    uint32_t ToNumber();

    inline uint8_t GetRed() { return this->m_red; }
    inline uint8_t GetGreen() { return this->m_green; }
    inline uint8_t GetBlue() { return this->m_blue; }

    inline void SetRed(uint8_t red) { this->m_red = red; }
    inline void SetGreen(uint8_t green) { this->m_green = green; }
    inline void SetBlue(uint8_t blue) { this->m_blue = blue; }

private:
    uint8_t m_red, m_green, m_blue;
};
