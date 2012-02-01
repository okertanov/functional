#include <iostream>
#include <string>


class Ftor
{
public: 
    Ftor(){};
    bool operator()(char* a){ std::cout << a; return true; };
};

template <typename F> void Method(char* data, size_t size, F ftor)
{
    ftor(data);
}

void main()
{
    char* data = "abcd";
    Method(data, strlen(data), Ftor());
}
