#include "BloomFilter_parallel.h"
#include <omp.h>

template <typename T>
BloomFilter_parallel<T>::BloomFilter_parallel(std::deque<T> my_set){
    this->my_set = my_set;
    this->n = this->my_set.size();
    this->m = abs((n * log(0.01))) / (log(2) * 2);
    this->k = (m/n)*log(2);
    initializeBloomFilter();
    add(my_set);
}

template <typename T>
void BloomFilter_parallel<T>::initializeBloomFilter(){

    bloom_filter = new bool[m];

    #pragma omp parallel for num_threads(omp_get_max_threads())
    for(size_t i=0; i<m; i++){
        bloom_filter[i] = false;
    }
}

template <typename T>
void BloomFilter_parallel<T>::add(std::deque<T> my_set){

    #pragma omp parallel for num_threads(omp_get_max_threads())
    for(size_t i=0; i<my_set.size(); i++){
        insert_element(my_set[i]);
    }
}

template <typename T>
bool* BloomFilter_parallel<T>::probably_contains(std::deque<T> elements){

    bool *results = new bool[elements.size()];

    #pragma omp parallel for num_threads(omp_get_max_threads())
    for(size_t i=0; i<elements.size(); i++){
        results[i] = check(elements[i]);
    }

    return results;
}

template <typename T>
void BloomFilter_parallel<T>::insert_element(T e)
{
    std::hash<T> h;

    for(size_t j=0; j<k; j++){
        size_t index = ((h(e)*(j+1))+n)%m;
        if(!bloom_filter[index]){bloom_filter[index] = true;}
    }
}

template <typename T>
bool BloomFilter_parallel<T>::check(T e){
    std::hash<T> h;
    bool probably_in = true;

    for(size_t i=0; i<k && probably_in; i++){
        size_t j = ((h(e)*(i+1))+n)%m;
        if(!bloom_filter[j])  probably_in = false;
    }

    return probably_in;
}
