#include "color.hpp"


U8Vec3 Color::ToFloats()
{
    return U8Vec3(
        this->m_red   / 255,
        this->m_green / 255,
        this->m_blue  / 255
    );
}


uint32_t Color::ToNumber()
{
    return (this->m_red   << 0)
         | (this->m_green << 8)
         | (this->m_blue  << 16);
}
