#include "math/color.hpp"

namespace Noctis
{

Vec3 Color::ToFloats()
{
    return Vec3(
        (float)this->m_red   / 255.f,
        (float)this->m_green / 255.f,
        (float)this->m_blue  / 255.f
    );
}

Vec4 Color::ToPaddedFloats()
{
    return Vec4(
        (float)this->m_red   / 255.f,
        (float)this->m_green / 255.f,
        (float)this->m_blue  / 255.f,
        0
    );
}


uint32_t Color::ToNumber()
{
    return (this->m_red   << 0)
         | (this->m_green << 8)
         | (this->m_blue  << 16);
}

}
