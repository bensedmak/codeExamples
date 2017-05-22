

#ifndef APR25_HASHTABLE_HASHTABLE_H
#define APR25_HASHTABLE_HASHTABLE_H

#include <functional> // std::function
#include <vector>

template <typename T>
using HashingFunction = std::function<int (const T &)>;

// HashingFunction<string>: std::function<int (const string &)>, and so on

template <typename T>
class Hashtable
{
private:
    HashingFunction<T> hash;
    std::vector<std::vector<T>> buckets;

public:
    Hashtable(int B, HashingFunction<T> hash);

    T & add(const T &value);
    bool remove(const T &value);
    T & get(const T &value);
    bool contains(const T &value) const;
    int maxBucketSize() const;
};

#include "Hashtable-impl.h"

#endif //APR25_HASHTABLE_HASHTABLE_H
