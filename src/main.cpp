#include <filesystem>

#include "core/window.hpp"
#include "core/project.hpp"
#include "editor/editor_ui.hpp"
#include "core/ecs/component/property.hpp"


int main() 
{
    Window window(800, 600, "Unknown Engine");

    std::string projPath = std::filesystem::absolute("test_project").string();
    Project::Init(projPath);

    EditorUI ui(window, "#version 330 core");

    // LOG_WARN("This is a warning.");
    // LOG_ERR("This is an error.");

    while (!window.ShouldClose())
    {
        ui.Render();
        
        window.PostRender();
    }

    return 0;
}

#if 0
#include <iostream>
#include "core/ecs/component/property.hpp"
#include "core/logger.hpp"


class A
{
public:

    ENABLE_REFLECTION(A)

    inline int &GetHealth() { return this->m_health; }
    PROPERTY_GETTER(GetHealth)

    inline const int GetTest() const { return this->test; }

private:
    PROPERTY_D(int, test, 1000)
    int m_health = 10;
};


struct B
{
    ENABLE_REFLECTION(B)
    PROPERTY_D(int, a, 100)
};


int main()
{
    A testClass;

    for (IProperty *property : testClass.GetProperties())
    {
        std::any value = property->GetValue(&testClass);
        if (value.type() == typeid(std::reference_wrapper<int>))
        {
            int &i = std::any_cast<std::reference_wrapper<int>>(value);
            i++;
            LOG_INFO("{} = {}", property->GetName(), testClass.GetTest());
        }
    }

    return 0;
}
#endif
