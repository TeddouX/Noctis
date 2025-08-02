#include "component.hpp"


template<typename T>
void to_json(json &j, const std::shared_ptr<T> &ptr) 
{
    if (ptr)
        j = *ptr;
    else
        j = nullptr;
}


template<typename T>
void from_json(const json &j, std::shared_ptr<T> &ptr) 
{
    if (!j.is_null())
    {
        ptr = std::make_shared<T>();
        from_json(j, *ptr);
    }
    else
        ptr = nullptr;       
}