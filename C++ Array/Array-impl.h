
#include <stdexcept>
#ifndef ASSIGNMENT_8_ARRAY_IMPL_H
#define ASSIGNMENT_8_ARRAY_IMPL_H
#include "Array.h"


template<typename T>
Array<T>::Array(int arraySize) {
    this->arraySize = arraySize;
    array = new T[arraySize];
}

template<typename T>
Array<T>::Array(const Array &old){
    arraySize = old.arraySize;
    array = new T[arraySize];
    for(int i = 0; i < arraySize; ++i){
        array[i] = old.array[i];
    }
}

template<typename T>
int Array<T>::length(){
    return arraySize;
}

template<typename T>
Array<T>::~Array() {
    delete[] array;
    array = nullptr;
}

template<typename T>
T Array<T>::get(int index) const{
    return array[index];
}

template<typename T>
void Array<T>::set(int index, T value) {
    array[index] = value;
}

template<typename T>
const Array<T> & Array<T>::operator=(const Array &original){
    if (this->arraySize < original.arraySize){
        delete[] this->array;
        this->array = nullptr;
        this->array = new T[original.arraySize];
    }
    this->arraySize = original.arraySize;
    for(int i = 0; i < this->arraySize; ++i){
        this->set(i,original.get(i));
    }
    return *this;
}

template<typename T>
const T & Array<T>::operator[](int i) const{
    if(i > this->arraySize){
        throw std::out_of_range("Index out of range");
    }
    else{
        return array[i];
    }
}

template<typename T>
T & Array<T>::operator[](int i) {
    if (i > this->arraySize) {
        throw std::out_of_range("Index out of range");
    } else {
        return array[i];
    }
}

#endif //ASSIGNMENT_8_ARRAY_IMPL_H
