#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h>
#include "stack.h"
#include "profiler.h"
#include "logger.h"

// function to create a stack of given capacity. It initializes size of 
// stack as 0 
struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->profArr = (Profile*)malloc(stack->capacity * sizeof(Profile));
    return stack;
}

// Stack is full when top is equal to the last index 
bool isFull(struct Stack* stack)
{
    return stack->top == (int) stack->capacity - 1;
}

// Stack is empty when top is equal to -1 
bool isEmpty(struct Stack* stack)
{
    return stack->top == -1;
}

// Function to add an item to stack.  It increases top by 1 
void push(struct Stack* stack, Profile item)
{
    assert(stack);
    if (isFull(stack))
        return;
    stack->profArr[++stack->top] = item;
    //logmsg("Profile %s pushed to stack\n", item.profileName);
}

// Function to remove an item from stack.  It decreases top by 1 
void pop(struct Stack* stack)
{
    assert(!isEmpty(stack));
    stack->profArr[stack->top--];
}

// Function to return the top from stack without removing it 
Profile peek(struct Stack* stack)
{
    assert(!isEmpty(stack));
    return stack->profArr[stack->top];
}
