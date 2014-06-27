#include <iostream>
#include <vector>
#include <memory>

class String
{
    public:
        String() : s_(NULL), l_(0)
        {
            std::cerr << "String.ctor" << std::endl;
        }

        virtual ~String()
        {
            std::cerr << "String.dtor" << std::endl;
        }

        String& operator=(const char* s)
        {
            std::cerr << "String.=" << std::endl;
            s_ = const_cast<char*>(s);
            l_ = std::strlen(s_);
            return *this;
        }

    private:
        char* s_;
        size_t l_;
};

class A
{
    public:
        A()
        {
            std::cerr << "A.ctor" << std::endl;
        }

        ~A()
        {
            std::cerr << "A.dtor" << std::endl;
        }

        String s;
};

int main()
{
    std::cerr << "main" << std::endl;

    A a;
    a.s = "absd";

    char** addr_priv_s = reinterpret_cast<char**>((intptr_t)&(a.s) + 1 * sizeof(intptr_t));
    int* addr_priv_l = reinterpret_cast<int*>((intptr_t)&(a.s) + 2 * sizeof(intptr_t));

    std::cerr << "\t\t" << addr_priv_s << " - " << addr_priv_l << std::endl;
    std::cerr << "\t\t" << "'" << *addr_priv_s << "'" << " of size " << *addr_priv_l << std::endl;

    return 0;
}
