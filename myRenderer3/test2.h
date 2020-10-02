#pragma once

#include <stdint.h>
//class Array {
//    void* m_Data; // pointer to array
//    unsigned int m_Size; // number of elements
//    unsigned int m_Capacity; // available memory size
//    unsigned int m_TypeSize; // size of element type
//public:
//    Array(uint32_t sizeElem)
//        : m_Data{ nullptr }, m_Size{ 0 }, m_Capacity{ 0 }, m_TypeSize{ sizeElem }
//    {}
//    bool isArrayEmpty(const Array* const arr);
//
//};
//

void testArray2();


template<typename T>
class Array {
private:
    void* m_Data; // pointer to array
    unsigned int m_Size; // number of elements
    unsigned int m_Capacity; // available memory size
    unsigned int m_TypeSize; // size of element type

    void clearArray();
    //
    //void* getArrayFront(const Array* const arr);
    
    void* reallocArray(void* block, size_t oldSize, size_t newSize);

    
    void checkArraySuffMem(void * ptr);
    
    //void eraseArrayAt(Array* const arr, unsigned int index);
    //
    //void removeAtFastArray(Array* const arr, unsigned int index);
    //
    //void printTestArray(const Array* const a);
public:
    Array(uint32_t sizeElem)
        : m_Data{ nullptr }, m_Size{ 0 }, m_Capacity{ 0 }, m_TypeSize{sizeElem}
    {}


    //Array createNewArray(unsigned int sizeElem);

    //Array createNewFilledArray(unsigned int numElem, unsigned int sizeElem);

    bool isArrayEmpty();

    int getArraySize();

    void addArraySize(int increment);

    int getArrayCapacity();

    int getArrayTypeSize();

    void pushBackArray(const T* srcData);

    /*void insertArray(Array * const dstArr, unsigned int index, const void * srcData);

    void * getArrayBack(const Array * const arr);

    void freeArray(Array * const dstArr);

    void * getArrayAt(const Array * const arr, unsigned int index);

    void popBackArray(Array * const arr);
*/
};


