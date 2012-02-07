/*
    g++ lambda.cpp -std=c++0x
*/

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <complex>

#ifndef __GNUG__
#define __PRETTY_FUNCTION__ __FUNCTION__
#endif

auto hof_make_iter() ->  std::function<void (std::string&)>
{
    std::cout << "Inside " << __PRETTY_FUNCTION__ << std::endl;

    int i = 0;

    return  [&i](std::string& s) -> void
            {
                std::cout << "Inside " << __PRETTY_FUNCTION__ << ": " <<  i++ << " => " << s << std::endl;
            };
}

auto hof_val(int a) -> std::function<int (int)>
{
    std::cout << "Inside " << __PRETTY_FUNCTION__ << ": a = " << a << std::endl;

    return [=](int b) -> int
    {
        std::cout << "Inside " << __PRETTY_FUNCTION__ << ": "<<
                     "a = " << a << " & " <<
                     "b = " << b << std::endl;
        return (a * b);
    };
}

auto hof_ref(int a) -> std::function<int (int)>
{
    std::cout << "Inside " << __PRETTY_FUNCTION__ << ": a = " << a << std::endl;

    return [&](int b) -> int
    {
        std::cout << "Inside " << __PRETTY_FUNCTION__ << ": "<<
                     "a = " << a << " & " <<
                     "b = " << b << std::endl;
        return (a * b);
    };
}

template <typename T>
auto pow2(const T x) -> decltype(x)
{
    return (x * x);
}

auto main(int argc, char** argv) -> int
{
    // 1. new init style
    std::vector<std::string> tdata {"123", "456", "789"};

    // 2. lambda
    std::for_each(tdata.begin(), tdata.end(), hof_make_iter());
    std::for_each(tdata.rbegin(), tdata.rend(), hof_make_iter());

    // 3. higher-order function
    auto ret1 = (hof_val(hof_val(1)(2))(3));
    auto ret2 = (hof_ref(hof_ref(1)(2))(3));

    std::cout << "1st lambda returned = " << ret1 << std::endl;
    std::cout << "2nd lambda returned = " << ret2 << std::endl;

    // 4. decltype
    auto px = pow2(std::complex<double>{2, 1});
    std::cout << "pow2({2, 1}) is " << px << std::endl;

    return 0;
}

