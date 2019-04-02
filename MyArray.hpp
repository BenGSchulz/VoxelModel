//
//  MyArray.hpp
//  Homework6
//
//  Created by Ben Schulz on 2/26/18.
//  Copyright © 2018 Ben Schulz. All rights reserved.
//

#ifndef MyArray_hpp
#define MyArray_hpp

#include <iostream>
#include <cstdint>
#include <stdio.h>
#include <cstdint>
#include <math.h>

template <typename T>
class MyArray {
private:
	T* array;
	uint32_t sizeV;
	uint32_t cap;

public:
	MyArray(uint32_t initSize = 0);
	MyArray(MyArray<T>& source);
	MyArray& operator=(MyArray<T>& source);
	~MyArray();
	
	T get(uint32_t index);
	void set(uint32_t index, T item);
	uint32_t size();
	void resize(uint32_t newSize);
	void pushBack(T item);
	T back();
	T popBack();
	T* getPointer();
	
};

template <typename T>
MyArray<T>::MyArray(uint32_t initSize) {
	array = new T[std::max(initSize, (uint32_t)20)];
	sizeV = 0;
	cap = initSize;
}

template <typename T>
MyArray<T>::MyArray(MyArray<T>& source) {
	sizeV = source.size();
	cap = source.cap;
	array = new T[cap];
	
	T* sourceArray = source.getPointer();
	
	for (uint32_t i = 0; i < sizeV; ++i) {
		array[i] = sourceArray[i];
	}
	
	sourceArray = nullptr;
}

template <typename T>
MyArray<T>& MyArray<T>::operator=(MyArray<T>& source) {
	if (this != &source) {
		delete [] array;
		sizeV = source.size();
		cap = source.cap;
		array = new T[cap];
		T* sourceArray = source.getPointer();
		
		for (uint32_t i = 0; i < sizeV; ++i) {
			array[i] = sourceArray[i];
		}
		
		sourceArray = nullptr;
	}
	
	return *this;
}

template <typename T>
MyArray<T>::~MyArray() {
	delete [] array;
	array = nullptr;
	sizeV = 0;
	cap = 0;
}

template <typename T>
T MyArray<T>::get(uint32_t index) {
	if (index >= sizeV) {
		std::cout << "No Item at Position: " << index << " -> Returning 0\n";
//		if (sizeV == 0) {
//			return array[sizeV];
//		} else {
//			return array[sizeV-1];
//		}
		return T();
	} else {
		return array[index];
	}
}

template <typename T>
void MyArray<T>::set(uint32_t index, T item) {
	if (index >= sizeV) {
		std::cout << "No Item at Position: " << index << "\n";
	} else {
		array[index] = item;
	}
}

template <typename T>
uint32_t MyArray<T>::size() {
	return sizeV;
}

template <typename T>
void MyArray<T>::resize(uint32_t newSize) {
	T* newArray = new T[newSize];
	
	uint32_t minSize = std::min(sizeV, newSize);
	
	for (uint32_t i = 0; i < minSize; ++i) {
		newArray[i] = array[i];
	}
	
	delete [] array;
	array = newArray;
	cap = newSize;
	
	newArray = nullptr;
	
}

template <typename T>
void MyArray<T>::pushBack(T item) {
	sizeV++;
	if (sizeV > cap) {
		resize(sizeV*2);
	}
	
	array[sizeV-1] = item;
}

template <typename T>
T MyArray<T>::back() {
	return array[sizeV-1];
}

template <typename T>
T MyArray<T>::popBack() {
	T result = back();
//	array[size()-1] = NULL;
	sizeV--;
	return result;
}

template <typename T>
T* MyArray<T>::getPointer() {
	return array;
}


#endif /* MyArray_hpp */
