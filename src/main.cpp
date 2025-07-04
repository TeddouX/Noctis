#if 0
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
#endif

#include <iostream>
#include "core/ecs/component/property.hpp"


class A
{
public:
    ENABLE_REFLECTION(A)
    PROPERTY_D(int, test, 1000)
};


int main()
{
    A testClass;

    for (auto prop : testClass.GetProperties())
    {
        std::any property = prop->GetProperty(&testClass);
        if (property.type() == typeid(std::reference_wrapper<int>))
        {
            int &i = std::any_cast<std::reference_wrapper<int>>(property);
            i++;
            std::cout << testClass.test << std::endl;
        }
    }

    return 0;
}
