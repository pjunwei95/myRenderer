#pragma once

struct Array {
    void* m_Data; // pointer to array
    int m_Size; // number of elements
    int m_Capacity; // available memory size
    unsigned int m_TypeSize; // size of element type
};

void testArray();

Array createNewArray(unsigned int sizeElem);

bool a_empty(const Array * const arr);

void a_push_back(Array * const dstArr, const void * srcData);

void * a_back(const Array * const arr);

void a_pop_back(Array * const arr);
