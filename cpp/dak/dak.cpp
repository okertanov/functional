//
// See http://maxim.livejournal.com/494874.html
//

#include <cstddef>
#include <cstdint>
#include <vector>
#include <iostream>
#include <chrono>
#include <emmintrin.h>

int64_t plain_sum(const std::vector<int64_t>& vec, int step) {
    const size_t size = vec.capacity();
    int64_t sum = 0;

    std::vector<int64_t> sums;
    sums.reserve(size - 1);
    for (size_t i = 0; i < size - 1; i++) {
        sums[i] = vec[i] + vec[i + 1];
    }

    for (size_t i = 0; i < size; i += step) {
        sum += sums[i];
    }

    return sum;
}

int64_t simd_sum(const std::vector<int64_t>& vec, int step) {
    const size_t size = vec.capacity();
    int64_t sum = 0;

    std::vector<int64_t> sums __attribute__((aligned(16)));
    sums.reserve(size);

    std::vector<int64_t>& avec = const_cast<std::vector<int64_t>&>(vec);

    for (size_t i = 0; i < size - 1; i += 2) {
        __m128i* av128_1 __attribute__((aligned(16))) = reinterpret_cast<__m128i*>(&avec[i]);
        __m128i av128_2 = _mm_loadu_si128(reinterpret_cast<__m128i*>(&avec[i + 1]));
        __m128i r = _mm_add_epi64(*av128_1, av128_2);
        _mm_store_si128((__m128i*)(&sums[i]), r);
    }

    for (size_t i = 0; i < size; i += step) {
        sum += sums[i];
    }

    return sum;
}

int main(int argc __attribute__((unused)), char** argv __attribute__((unused))) {
    const int step = 100;
    const int runs = 20;
    const size_t size = 1000000;

    int64_t sum1 = 0ull, sum2 = 0ull;

    // Prepare data
    std::vector<int64_t> vec1;
    vec1.reserve(size);
    for (size_t i = 0; i < size; i++) {
        vec1[i] = i;
    }

    // SIMD Sum
    auto start1 = std::chrono::high_resolution_clock::now();
    for (int e = 0; e < runs; e++) {
        sum1 = simd_sum(vec1, step);
    }
    auto end1 = std::chrono::high_resolution_clock::now();
    auto diff1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count();

    // Reset Caches?

    // Plain Sum
    auto start2 = std::chrono::high_resolution_clock::now();
    for (int e = 0; e < runs; e++) {
        sum2 = plain_sum(vec1, step);
    }
    auto end2 = std::chrono::high_resolution_clock::now();
    auto diff2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count();

    // Dump
    std::cout << sum1 << " -- time for simd:  " << diff1 << " ms." << std::endl;
    std::cout << sum2 << " -- time for plain: " << diff2 << " ms." << std::endl;

    return EXIT_SUCCESS;
}
