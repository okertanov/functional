/*
    Oleg Kertanov (c) 2005
*/


#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include <iterator>
#include <numeric>
#include <functional>
#include <algorithm>

#define _() do { std::cout << std::endl << __FILE__ << ":" << __LINE__ << " in " << __FUNCTION__ << "()" << std::endl; } while (0)

static const int fillValues[] = {0,1,2,3,4,5,6,7};

void vec_as_string()
{
    _();
    std::string str("Any string content.");

    /*don't! ::strcpy(str1, "add me!");*/
    std::vector<char> vect;
    vect.assign(str.begin(), str.end());
    ::strcpy(&vect[0], "copy me!");

    ::printf("%s\n", &vect[0]);
}

void vec_fill_and_remove()
{
    _();
    std::vector<int> vec(fillValues, fillValues + sizeof(fillValues)/sizeof(int));

    std::cout << std::accumulate(&fillValues[0], &fillValues[5], 1) << std::endl;

    vec.erase(remove(vec.begin(), vec.end(), 0), vec.end());
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

void vec_not1()
{
    _();
    std::vector<int> vec(fillValues, fillValues+sizeof(fillValues)/sizeof(int));
    std::vector <int>::const_iterator reit = find_if(vec.begin(), vec.end(), 
            std::not1(std::bind2nd(std::greater<int>(), 5)));
    std::cout << *reit << std::endl;
}

void vec_bind2nd()
{
    _();
    std::vector<int> vec(fillValues, fillValues+sizeof(fillValues)/sizeof(int));
    std::vector <int>::const_iterator reit = find_if( vec.begin(), vec.end(), 
            std::bind2nd(std::greater<int>(), 5) );
    std::cout << *reit << std::endl;
}

void verse_iterator_find_if()
{
    _();
    std::vector<int> vec(fillValues, fillValues+sizeof(fillValues)/sizeof(int));
    std::vector<int>::iterator start(vec.end());
    std::vector<int>::iterator finish(vec.begin());
    std::vector<int>::iterator ret = 
            std::find_if( start, finish, std::bind2nd(std::less<int>(), 5) );
    std::cout << *ret << std::endl;
}

void reverse_iterator_find_if()
{
    _();
    std::vector<int> vec(fillValues, fillValues+sizeof(fillValues)/sizeof(int));
    std::reverse_iterator<std::vector<int>::iterator> start(vec.end());
    std::reverse_iterator<std::vector<int>::iterator> finish(vec.begin());
    std::vector<int>::reverse_iterator ret = 
            std::find_if( start, finish, std::bind2nd(std::less<int>(), 5) );
    std::cout << *ret << std::endl;
}

void inner_product()
{
    _();
    //1*3+2*2+3*1=10
    const int lim = 3;
    int first[lim] = {1,2,3};
    int second[lim] = {3,2,1}; 
    
    std::cout << std::inner_product(&first[0], &first[lim], &second[0], 0) << std::endl;
}

void descending_sort()
{
    _();
    std::deque<int> deq;
    for(int i = 0; i < 10; i++) deq.push_back(i);
    std::sort(deq.begin(), deq.end(), std::greater<int>());
    std::copy(deq.begin(), deq.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

void deque_push_erase()
{
    _();
    std::deque<int> deq;
    for(int i = 0; i < 10; i++) deq.push_front(i);
    deq.erase(remove(deq.begin(), deq.end(), 1), deq.end());
    std::copy(deq.begin(), deq.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

void deque_invalidate()
{
    _();
    std::deque<int> deq;
    deq.push_back(0xFF);
    
    for(int i = 0; i < 10; i++)
    {
        std::deque<int>::const_iterator beg_it = deq.begin();
        deq.push_back(i);
        std::cout << "The first deque value is: " << *beg_it << std::endl;
    }
}

void deque_assign()
{
    _();
    std::deque<int> deq;
    deq.assign(3, 0x0AFAFFEB);
    std::copy(deq.begin(), deq.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

int main(int argc, char** argv)
{
    _();
    vec_as_string();
    vec_fill_and_remove();
    vec_not1();
    vec_bind2nd();
    verse_iterator_find_if();
    reverse_iterator_find_if();
    inner_product();
    descending_sort();
    deque_push_erase();
    deque_invalidate();
    deque_assign();

    return EXIT_SUCCESS;
}

