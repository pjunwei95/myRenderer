#pragma once

struct Array {
    void* m_Data; // pointer to array
    unsigned int m_Size; // number of elements
    unsigned int m_Capacity; // available memory size
    unsigned int m_TypeSize; // size of element type
};

//void testArray();

Array createNewArray(unsigned int sizeElem);

Array createNewFilledArray(unsigned int numElem, unsigned int sizeElem);

bool isArrayEmpty(const Array * const arr);

int getArraySize(const Array * const arr);

void addArraySize(Array * const arr, int increment);

int getArrayCapacity(const Array * const arr);

int getArrayTypeSize(const Array * const arr);

void pushBackArray(Array * const dstArr, const void * srcData);

void insertArray(Array * const dstArr, unsigned int index, const void * srcData);

void * getArrayBack(const Array * const arr);

void freeArray(Array * const dstArr);

void * getArrayAt(const Array * const arr, unsigned int index);

void popBackArray(Array * const arr);
