
#ifndef APR25_HASHTABLE_HASHTABLE_IMPL_H
#define APR25_HASHTABLE_HASHTABLE_IMPL_H

#include "Hashtable.h"

#include <algorithm> // find()
#include <stdexcept> // runtime_error

template <typename T>
Hashtable<T>::Hashtable(int B, HashingFunction<T> hash) :
    hash(hash),
    buckets(B)
{}

template <typename T>
T & Hashtable<T>::add(const T &value)
{
    int hashcode = hash(value);
    int b = hashcode % buckets.size();
    auto &bucket = buckets[b];

    auto it = std::find(bucket.begin(), bucket.end(), value);
    if (it == bucket.end())
    {
        // The value is not in the bucket
        bucket.push_back(value);
        return bucket.back();
    }
    else
        return *it;
}

template <typename T>
T & Hashtable<T>::get(const T &value)
{
    int hashcode = hash(value);
    int b = hashcode % buckets.size();
    auto &bucket = buckets[b];

    auto it = std::find(bucket.begin(), bucket.end(), value);
    if (it != bucket.end())
        return *it;
    else
        throw std::runtime_error("Element not in hashtable");
}

template <typename T>
bool Hashtable<T>::remove(const T &value)
{
    int hashcode = hash(value);
    int b = hashcode % buckets.size();
    auto &bucket = buckets[b];
    auto it = std::find(bucket.begin(), bucket.end(), value);
    if (it != bucket.end())
    {
        bucket.erase(it);
        return true;
    }
    else return false;
}

template<typename T>
bool Hashtable<T>::contains(const T &value) const {
    int hashcode = hash(value);
    int b = hashcode % buckets.size();
    auto &bucket = buckets[b];
    auto it = std::find(bucket.begin(), bucket.end(), value);
    return it != bucket.end();
}

template<typename T>
int Hashtable<T>::maxBucketSize() const {
    int maxSize = 0;
    for (auto bucket : buckets){
        if (bucket.size() > maxSize)
            maxSize = bucket.size();
    }
    return maxSize;
}

#endif //APR25_HASHTABLE_HASHTABLE_IMPL_H
