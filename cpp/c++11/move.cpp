/*
    g++ move.cpp -std=c++0x
*/

#include <string>
#include <iostream>

class A
{
    public:
        A(int handle) : handle_(handle)
        {
            std::cout << "Inside " << __PRETTY_FUNCTION__ << std::endl;
        }
        A(const A& a)
        {
            std::cout << "Inside " << __PRETTY_FUNCTION__ << std::endl;
            handle_ = a.handle_;
        }
        A(A&& a)
        {
            std::cout << "Inside " << __PRETTY_FUNCTION__ << std::endl;
            handle_ = a.handle_, a.handle_ = 0;
        }
        int handle() const
        {
            return handle_;
        }
    private:
        int handle_;
};

std::ostream& operator<< (std::ostream& os, const A& a)
{
    os << "handle_ = " << a.handle();
    return os;
}

int main()
{
    A a1(1);
    A a2(a1);
    A a3(std::move(a2));
    A a4(std::forward<A>(5));

    std::cout << "a1 = " << a1 << ", " << std::endl <<
                 "a2 = " << a2 << ", " << std::endl <<
                 "a3 = " << a3 << ", " << std::endl <<
                 "a4 = " << a4 << ", " << std::endl;

    return 0;
}

