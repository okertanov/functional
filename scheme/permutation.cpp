//
// BUILD: cl -GX -DWIN32 -O2 permutation.cpp -lm -o permutation.exe
//        g++ -O2 permutation.cpp -o permutation.exe -lm
// (c) Andrew  Kuhar: Generic Algorithm
// (c) Oleg Kertanov: STL Algorithm, Timers
//

#include <ostream>
#include <iostream>
#include <iterator>
#include <algorithm>

#if defined(WIN32)
#include <windows.h>
#else
#include <sys/time.h>
#endif

void TestOne();
void TestTwo();

namespace benchmark
{

namespace timer
{

class PerfTimer
{
    private:
        void Init()
        {
            startTime = stopTime = 0;
            #if defined(WIN32)
            LARGE_INTEGER freq;
            QueryPerformanceFrequency(&freq);
            millFreq = ((double)freq.QuadPart) / 1000;
            #else
            millFreq = 1000;
            #endif
        }
        void Start()
        {
            #if defined(WIN32)
            LARGE_INTEGER freq;
            QueryPerformanceCounter(&freq);
            startTime = freq.QuadPart / millFreq;
            #else
            timeval tv;
            gettimeofday(&tv, NULL);
            startTime = ((tv.tv_sec * 1000000) + tv.tv_usec) / millFreq;
            #endif
        }
        void Stop()
        {
            #if defined(WIN32)
            LARGE_INTEGER freq;
            QueryPerformanceCounter(&freq);
            stopTime = freq.QuadPart / millFreq;
            #else
            timeval tv;
            gettimeofday(&tv, NULL);
            stopTime = ((tv.tv_sec * 1000000) + tv.tv_usec) / millFreq;
            #endif
        }
        void Dump() const
        {
            std::cerr << std::endl << blockName.c_str() << " ";
            std::cerr << "Time: " << (stopTime - startTime) << std::endl;
        }
        double startTime;
        double stopTime;
        double millFreq;
        std::string blockName;
    public:
        PerfTimer()
        {
            blockName = "<default block>";
            Init();
            Start();
        }
        PerfTimer(const std::string& bn) : blockName(bn)
        {
            Init();
            Start();
        }
        ~PerfTimer()
        {
            Stop();
            Dump();
        }
};

} //benchmark::timer

namespace algorithm
{
    class Perm
{
    unsigned char *Value;
    int length, count;
    int Factorial(int n);
public:
    Perm() { Value = 0; }
    void Begin(const unsigned char* s);
    Perm(const unsigned char* s) { Value = 0; Begin(s); }
    const unsigned char* Next();
    int Count() { return count; }
    int Length() { return length; }
    operator const unsigned char* () { return Value + 1; }
    ~Perm() { if(Value) delete Value; }
};

int Perm::Factorial(int n)
{
    int f = 1; for(int i = 2; i <= n; i++) f *= i;
    return f;
}

void Perm::Begin(const unsigned char* s)
{
    if(Value) delete Value;
    length = 0; for(const unsigned char* p = s; *p; p++) length++;
    Value = new unsigned char[length + 2]; if(!Value) return;
    int Symbols[256], i; for(i = 0; i < 256; i++) Symbols[i] = 0;
    *Value = 0; unsigned char* l = Value + 1; do { Symbols[*s]++; } while((*l++ = *s++) != 0);
    count = Factorial(length); for(i = 0; i < 256; i++) count /= Factorial(Symbols[i]);
}

const unsigned char* Perm::Next()
{
    if(length == 0) return Value + 1;
    unsigned char *p, *l, t;
    for(p = Value + length - 1; *p >= *(p + 1); p--);
    if((t = *p) != 0) { for(l = p + 1; *l > t; l++); *p = *(--l); *l = t; }
    l = Value + length; for(p++; l > p; p++) { t = *p; *p = *l; *l-- = t; }
    return Value + 1;
}

} //benchmark::algorithm

} //namespace benchmark

void TestOne()
{
    benchmark::timer::PerfTimer* timer = new benchmark::timer::PerfTimer("STL Permutation");
    std::string* stringData = new std::string("012");
    do
    {
#ifdef USE_STDOUT
        std::cout << stringData->c_str() << std::endl;
#endif
    } while (std::next_permutation(stringData->begin(), stringData->end()));
    delete stringData;
    delete timer;
}

void TestTwo()
{
    benchmark::timer::PerfTimer* timer = new benchmark::timer::PerfTimer("Generic Permutation");
    benchmark::algorithm::Perm P((unsigned char*)"012");

#ifdef USE_STDOUT
    std::cout << P << std::endl;
#endif
    for(int i = 1; i < P.Count(); i++)
    {
#ifdef USE_STDOUT
        std::cout << P.Next() << std::endl;
#else
        P.Next();
#endif
    }

    delete timer;
}


int main(int argc, char** argv)
{
#if defined(WIN32)
    Sleep(1000);
#else
    sleep(1);
#endif

    TestOne(); //STL
    TestTwo(); //Generic

    return 0;
}

