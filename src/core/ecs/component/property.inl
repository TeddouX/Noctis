#include "property.hpp"


template <typename T, typename C>
std::string MemberProperty<T, C>::GetBeautifiedName() const
{
    std::string beautifiedName = this->m_name;
    beautifiedName[0] = toupper(beautifiedName[0]);

    return SplitStringAtCapital(beautifiedName);
}


template <typename T, typename C>
std::any MemberProperty<T, C>::GetValue(void *C_instance) const
{
    C* obj = static_cast<C*>(C_instance);
    return std::ref(obj->*m_member);
}


template <typename T, typename C>
std::string GetterProperty<T, C>::GetBeautifiedName() const
{
    std::string beautifiedName = this->m_name;
    beautifiedName[0] = toupper(beautifiedName[0]);

    std::regex pattern("Get", std::regex_constants::icase);
    beautifiedName = std::regex_replace(beautifiedName, pattern, "");

    return SplitStringAtCapital(beautifiedName);
}


template <typename T, typename C>
std::any GetterProperty<T, C>::GetValue(void *C_instance) const
{
    C* obj = static_cast<C*>(C_instance);
    return std::ref((obj->*m_getter)());
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
