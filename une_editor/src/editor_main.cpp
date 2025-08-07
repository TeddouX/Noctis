#include "editor.hpp"


int main()
{
    Editor::Init();
    Editor::GetInstance()->Run();
    
    return 0;
}
