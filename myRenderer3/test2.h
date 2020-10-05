#pragma once

#include <stdint.h>
void testArray2();


template<typename T>
class Array {
private:
    T* m_Data; // pointer to array
    uint32_t m_Size; // number of elements
    uint32_t m_Capacity; // available memory size
    uint32_t m_TypeSize; // size of element type

    //void clearArray();
    //
    //
    //void* reallocArray(void* block, size_t oldSize, size_t newSize);

    //
    void checkArraySuffMem();
    //
    //
    
public:
    Array()
        : m_Data{ nullptr }, m_Size{ 0 }, m_Capacity{ 0 }, m_TypeSize{sizeof(T)}
    {}


    //Array createNewArray(unsigned int sizeElem);

    //Array createNewFilledArray(unsigned int numElem, unsigned int sizeElem);

    bool isArrayEmpty() const;

  /*  int getArraySize() const;

    void addArraySize(int increment);

    int getArrayCapacity() const;

    int getArrayTypeSize() const;*/

    void pushBackArray(const T* srcData);

    void printTestArray();

    void eraseArrayAt(uint32_t index);

    void insertArray(uint32_t index, const T* srcData);
    
    T* getArrayFront() const;

    T* getArrayBack() const;

    //void freeArray(Array * const dstArr);

    T* getArrayAt(uint32_t index) const;

    void popBackArray();
    void removeAtFastArray(uint32_t index);

};


