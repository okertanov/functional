/*
    Oleg Kertanov (c) 2005
*/

/* How to use:
   benchmark::timer::PerfTimer* timer = new benchmark::timer::PerfTimer("Generic Permutation");
*/

#include <iostream>
#include <iterator>
#include <algorithm>

#if defined(WIN32)
#include <windows.h>
#else
#include <sys/time.h>
#endif

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

} //timer

} //benchmark

