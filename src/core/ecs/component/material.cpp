#include "material.hpp"


void Material::UploadData()
{
    // Color          + 16 bytes
    // SpecReflect    + 12 bytes
    // SpecDefinition + 4 bytes
    // Total          = 32 bytes
    // CCCCCCCCCCCC----
    // RRRRRRRRRRRRDDDD
    Material::Data data {
        this->color.ToPaddedFloats(),
        this->specularReflectance.ToFloats(),
        this->specularDefinition
    };

    this->m_ssbo.UploadData(data);
}
