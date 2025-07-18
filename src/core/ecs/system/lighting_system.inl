#include "lighting_system.hpp"


template <typename T>
void LightingSystem::UploadLights(const std::vector<T> &lights, SSBO<T> ssbo)
{
    uint32_t count = (uint32_t)lights.size();
    size_t padding = 16 - sizeof(uint32_t);

    // uint32   - 4 bytes
    // padding  - 12 bytes
    // lights[] - variable (but always aligned to 16 bytes) 

    size_t totalSize = sizeof(uint32_t) + padding + sizeof(T) * count;

    // Allocate buffer
    std::vector<uint8_t> buffer(totalSize);

    // Write the count at the begining of the buf
    std::memcpy(buffer.data(), &count, sizeof(uint32_t));

    // Padding because objects are 16 bytes aligned in std430
    std::memset(buffer.data() + sizeof(uint32_t), 0, padding);

    // Write the light data after the count
    std::memcpy(
        buffer.data() + sizeof(uint32_t) + padding, 
        lights.data(), 
        sizeof(T) * count
    );

    ssbo.UploadRaw(buffer.data(), buffer.size());
}
