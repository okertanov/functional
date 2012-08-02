/**
    @file       add1.cpp
    @brief      Increments items in an array matching specified value.

    @author     Oleg Kertanov <okertanov@gmail.com>
    @date       August 2012

    @see        http://blog.jazzychad.net/2012/08/01/array-iteration-problem.html
                    and
                http://news.ycombinator.com/item?id=4326382

    Implement the following function:

add1 - increments items in an array matching specified value

param: arr - array of integers to manipulate
param: val - integer, value to increment
param: n   - integer, control value specifying behavior of manipulation
  n == 0 means increment all occurrences of val

  n > 0  means increment up to n occurrences of val
         from left-to-right (forward)

  n < 0  means increment up to n occurrences of val
         from right-to-left (backward)

return: arr with proper values incremented

    Examples:

# add1 [1,4,1,5,1], 1, 0  -> [2,4,2,5,2]
# add1 [1,4,1,5,1], 1, 2  -> [2,4,2,5,1]
# add1 [1,4,1,5,1], 1, -2 -> [1,4,2,5,2]

    To build:

g++ -std=c++0x -o add1 add1.cpp

*/

#include <cmath>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <deque>

namespace Exec
{

/**
    @typedef Exec::IntegerArray
    @brief
*/
typedef std::deque<int>    IntegerArray;

/**
    @fn Exec::add1_impl()
    @brief
*/
template <typename T, typename InputIterator>
bool add1_impl(const InputIterator& begin,  const InputIterator& end, const typename T::value_type& value, const signed long n)
{
    auto found = begin;
    auto count = ( n ? std::abs(n) : std::distance(begin, end) );

    do
    {
        found = std::find_if(begin, end,
                [&](typename T::value_type curr) -> bool
                {
                    return (curr == value);
                }
        );

        if ( found != end )
        {
            (*found)++;
        }
    }
    while ( --count > 0 && found != end );

    return true;
}

/**
    @fn Exec::add1()
    @brief
*/
template <typename T>
T add1(T& array, const typename T::value_type& value, const signed long n)
{
    if ( n < 0 )
    {
        add1_impl<T>(array.rbegin(), array.rend(), value, n);
    }
    else
    {
        add1_impl<T>(array.begin(), array.end(), value, n);
    }

    return array;
}

} // namespace Exec

/**
    @fn ::operator<< ()
    @brief
*/
std::ostream& operator<< (std::ostream& os, const Exec::IntegerArray& array)
{
    std::copy(array.begin(), array.end(), std::ostream_iterator<int>(os, " "));
    return os;
}

/**
    @fn main()
    @brief
*/
auto main(int argc, char* argv[]) -> int
{
    const Exec::IntegerArray reference_vec = {1, 4, 1, 5, 1};

    Exec::IntegerArray test_vec1(reference_vec),
                       test_vec2(reference_vec),
                       test_vec3(reference_vec);

    std::cout << test_vec1 << std::endl
              << test_vec2 << std::endl
              << test_vec3 << std::endl;

    std::cout << "~~~~~~~~~" << std::endl;

    std::cout << Exec::add1(test_vec1, 1, 0)  << std::endl
              << Exec::add1(test_vec2, 1, 2)  << std::endl
              << Exec::add1(test_vec3, 1, -2) << std::endl;
}

