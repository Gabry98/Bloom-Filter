#include "BloomFilter.h"
template <typename T>
BloomFilter<T>::BloomFilter(std::deque<T> my_set){
    this->my_set = my_set;
    this->n = this->my_set.size();
    this->m = abs((n * log(0.01))) / (log(2) * 2);
    this->k = (m/n)*log(2);
    initializeBloomFilter();
    add(my_set);
}

template <typename T>
void BloomFilter<T>::initializeBloomFilter(){
    bloom_filter = new bool[m];
    for(size_t i=0; i<m; i++){
        bloom_filter[i] = false;
    }
}

template <typename T>
void BloomFilter<T>::add(std::deque<T> my_set){
    std::hash<T> h;
    while(!my_set.empty()){
        for(size_t j=0; j<k; j++){
            size_t index = ((h(my_set.front())*(j+1))+n)%m;
            if(!bloom_filter[index]){bloom_filter[index] = true;}
        }
        my_set.pop_front();
    }
}

template <typename T>
bool* BloomFilter<T>::probably_contains(std::deque<T> elements){

    bool *results = new bool[elements.size()];

    for(size_t i=0; i<elements.size(); i++){
        results[i] = check(elements[i]);
    }

    return results;
}

template <typename T>
bool BloomFilter<T>::check(T e){
    std::hash<T> h;
    bool probably_in = true;

    for(size_t i=0; i<k && probably_in; i++){
        size_t j = ((h(e)*(i+1))+n)%m;
        if(!bloom_filter[j])  probably_in = false;
    }

    return probably_in;
}
