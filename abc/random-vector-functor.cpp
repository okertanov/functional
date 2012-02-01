#include <ctime>
#include <limits>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <stdexcept>

typedef unsigned char       byte;
typedef std::vector<byte>   bytearray; 

template<typename T> class RandomNumberT 
{
public:
    RandomNumberT() 
    { 
        std::srand(std::time(NULL)); 
    }
    T operator()() const 
    { 
        T rand = std::rand() % (std::numeric_limits<T>::max() + 1); 
        return (rand);
    }
};

int main (int argc, char* argv[]) 
{
    try 
    {
        const size_t buf_size = 1024 * 1024;
        bytearray yuv_buffer(buf_size);
        std::generate(yuv_buffer.begin(), yuv_buffer.end(), RandomNumberT<byte>());
        
        std::cout << "YUV vector initialized with " << buf_size << " signature: "
                  << yuv_buffer[0] << yuv_buffer[1] << yuv_buffer[2] << std::endl;

        const bytearray::iterator i1 = std::find(yuv_buffer.begin(), yuv_buffer.end(), std::numeric_limits<byte>::max());
        const bytearray::iterator i2 = std::find(yuv_buffer.begin(), yuv_buffer.end(), std::numeric_limits<byte>::max()-1);
        assert(i2 != yuv_buffer.end());
        std::cout << "Found " << static_cast<int>(std::numeric_limits<byte>::max() - 1) << " is: " 
                                    << static_cast<int>(*i2) << " at position: " 
                                    << std::distance(yuv_buffer.begin(), i2) << std::endl;
        assert(i1 != yuv_buffer.end());
        std::cout << "Found " << static_cast<int>(std::numeric_limits<byte>::max()) << " is: " 
                                    << static_cast<int>(*i1) << " at position: " 
                                    << std::distance(yuv_buffer.begin(), i1) << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
