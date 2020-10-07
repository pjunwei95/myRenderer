#pragma once
#include <stdint.h>

void testArray2();

template<typename T>
class Array {
private:
    T* m_Data; // pointer to array
    uint32_t m_Size; // number of elements
    uint32_t m_Capacity; // available memory size

    //deprecated
    //uint32_t m_TypeSize; // size of element type

    void checkArraySuffMem();
public:
    Array();
    // new filled array of fixed size
    Array(uint32_t numElem);
    ~Array();
    
    bool isArrayEmpty() const;
    void addArraySize(int increment);
    uint32_t getArraySize() const;
    uint32_t getArrayCapacity() const;
    T* getArrayFront() const;
    T* getArrayBack() const;
    T* getArrayAt(uint32_t index) const;
    void pushBackArray(const T* srcData);
    void popBackArray();
    void eraseArrayAt(uint32_t index);
    void insertArray(uint32_t index, const T* srcData);
    void clearArray();
    void removeAtFastArray(uint32_t index);
    void printTestArray();

    //DEPRECATED
    //Array createNewArray(unsigned int sizeElem);

    //Array createNewFilledArray(unsigned int numElem, unsigned int sizeElem);

    //void* reallocArray(void* block, size_t oldSize, size_t newSize);

    //int getArrayTypeSize() const;

    //void freeArray();

};


