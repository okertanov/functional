#include <iostream>
#include <string>

struct SomeParser
{
    SomeParser(const std::string& str) : str_("str")
    {
    }

    int operator+()
    {
        return str_.length();
    }

    std::string str_;
};

int main()
{
    std::cout << +SomeParser("One") << std::endl;
}

