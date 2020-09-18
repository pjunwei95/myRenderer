#pragma once

struct Array {
    void* m_Data; // pointer to array
    unsigned int m_Size; // number of elements
    unsigned int m_Capacity; // available memory size
    unsigned int m_TypeSize; // size of element type
};

void testArray();

Array a_create_new(unsigned int sizeElem);

Array a_create_new_filled(unsigned int numElem, const void * const elemVal, unsigned int sizeElem);

bool a_empty(const Array * const arr);

void a_push_back(Array * const dstArr, const void * srcData);

void a_insert(Array * const dstArr, unsigned int index, const void * srcData);

void * a_back(const Array * const arr);

void a_free(Array * const dstArr);

void * a_at(const Array * const arr, unsigned int index);

void a_pop_back(Array * const arr);
