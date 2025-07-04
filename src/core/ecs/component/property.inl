#include "property.hpp"

template <typename T, typename C>
Property<T, C>::Property(const std::string &name, T C::*member)
        : m_name(name), m_member(member) 
{
}


template <typename T, typename C>
std::any Property<T, C>::GetProperty(void *C_instance) const
{
    C* obj = static_cast<C*>(C_instance);
    return std::ref(obj->*m_member);
}



template <typename C>
void PropertyRegistry<C>::RegisterProperty(const std::string &name, std::shared_ptr<IProperty> prop)
{
    PropertyRegistry::GetPropertyList().emplace_back(std::move(prop));
}


template <typename C>
std::vector<std::shared_ptr<IProperty>> &PropertyRegistry<C>::GetPropertyList()
{
    static std::vector<std::shared_ptr<IProperty>> props;
    return props;
}
