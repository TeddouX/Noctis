#include "ecs/component/property.hpp"


std::string SplitStringAtCapital(std::string &str)
{
    std::string output;

    for (char ch : str)
    {
        // The char is an uppercase letter and its not the first char of the string
        if (isupper(ch) && str[0] != ch)
            output += std::string(" ") + ch;
        else
            output += ch;
    }

    return output;
}
