#include <stdint.h>

#include "../ssbo.hpp"

namespace Noctis
{
    
class NOCTIS_API SSBOOpenGL : public SSBO {
public:
    SSBOOpenGL(int bindPoint);

    void uploadData(size_t size, void *data) override;
    void updateData(size_t offset, size_t size, void *data) override;

private:
    uint32_t ID_;
};
    
} // namespace Noctis
