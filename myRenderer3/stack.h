//#pragma once
//#include "array.h"
//
//template <typename T>
//class Stack {
//public:
//    Stack(){}
//
//    ~Stack(){}
//
//    void push(T* srcData)
//    {
//        m_Stack.pushBack(srcData);
//    }
//    void pop()
//    {
//        m_Stack.popBack();
//    }
//    const T& peek()
//    {
//        return m_Stack.back();
//    }
//    uint32_t size()
//    {
//        return m_Stack.size();
//    }
//
//    const T& at(uint32_t index);
//
//
//private:
//    Array<T> m_Stack;
//};
//
//template <typename T>
//const T& Stack<T>::at(uint32_t index)
//{
//    assert(index < size());
//    return m_Stack.at(index);
//}
//
