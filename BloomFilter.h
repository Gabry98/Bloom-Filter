#ifndef BLOOMFILTER_H_INCLUDED
#define BLOOMFILTER_H_INCLUDED
#include <iostream>
#include <math.h>
#include <functional>
#include <queue>

using namespace std;

template <typename T>
class BloomFilter{

private:
    bool *bloom_filter;
    std::deque<T> my_set;
    size_t m;
    size_t n;
    size_t k;
    void initializeBloomFilter();
    void add(std::deque<T> my_set);
    bool check(T e);

public:
    BloomFilter(std::deque<T> my_set);
    bool* probably_contains(std::deque<T> elements);

};

#endif // BLOOMFILTER_H_INCLUDED
