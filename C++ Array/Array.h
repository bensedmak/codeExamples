
#ifndef ASSIGNMENT_8_ARRAY_H
#define ASSIGNMENT_8_ARRAY_H

template <typename T>
class Array{
private:
    int arraySize;
    T *array;

public:
    Array(int arraySize);
    Array(const Array &old);
    int length();
    T get(int index) const;
    void set(int index, T value);
    ~Array();
    const Array & operator=(const Array &original);
    const T & operator[](int i) const;
    T & operator[](int i);
};

#include "Array-impl.h"

#endif //ASSIGNMENT_8_ARRAY_H
