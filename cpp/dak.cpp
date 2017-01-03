//
// See http://maxim.livejournal.com/494874.html
//
// c++ -O3 -Wall -Wextra -std=c++11 -o dak dak.cpp
//

#include <cstdint>
#include <vector>
#include <iostream>
#include <chrono>

int main() {
    int64_t sum = 0;

   auto start = std::chrono::high_resolution_clock::now();

    for (int e = 0; e < 20; e++) {
        sum = 0;

        std::vector<int64_t> x;
        x.reserve(1000000);
        for (int i = 0; i < 1000000; i++) {
            x[i] = i;
        }

        std::vector<int64_t> y;
        y.reserve(1000000 - 1);
        for (int i = 0; i < 1000000-1; i++) {
            y[i] = x[i] + x[i+1];
        }

        for (int i = 0; i < 1000000; i += 100) {
            sum += y[i];
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << sum << std::endl;
    std::cout << "time: " <<  diff << " ms" << std::endl;
}
