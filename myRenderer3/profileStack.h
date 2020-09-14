#pragma once
#include "profiler.h"

// A structure to represent a stack 
struct Stack {
    int top;
    unsigned capacity;
    Profile *array;
};

Stack * createStack(unsigned capacity);

bool isEmpty(Stack * stack);

void push(Stack * stack, Profile item);

void pop(Stack * stack);

Profile peek(Stack * stack);
