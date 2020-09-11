#include "test.h"
#include <iostream>
#include <iomanip>

#include <string.h>

typedef struct {
    uint8_t * const buffer;
    int head;
    int tail;
    const int maxlen;
} CircularBuffer;

#define CIRC_BBUF_DEF(x,y)                \
    uint8_t x##_data_space[y];            \
    CircularBuffer x = {                     \
        x##_data_space,         \
        0,                        \
        0,                        \
        y                       \
    }


int circ_bbuf_push(CircularBuffer *c, uint8_t data)
{
    int next;

    next = c->head + 1;  // next is where head will point to after this write.
    if (next >= c->maxlen)
        next = 0;

    if (next == c->tail)  // if the head + 1 == tail, circular buffer is full
        return -1;

    c->buffer[c->head] = data;  // Load data and then move
    c->head = next;             // head to next data offset.
    return 0;  // return success to indicate successful push.
}

int circ_bbuf_pop(CircularBuffer *c, uint8_t *data)
{
    int next;

    if (c->head == c->tail)  // if the head == tail, we don't have any data
        return -1;

    next = c->tail + 1;  // next is where tail will point to after this read.
    if (next >= c->maxlen)
        next = 0;

    *data = c->buffer[c->tail];  // Read data and then move
    c->tail = next;              // tail to next offset.
    return 0;  // return success to indicate successful push.
}


void test()
{
    CIRC_BBUF_DEF(my_circ_buf, 6);
    uint8_t out_data = 0, in_data = 0x55;
    uint8_t test = 0x66;

    circ_bbuf_push(&my_circ_buf, in_data);
    circ_bbuf_push(&my_circ_buf, test);
    circ_bbuf_push(&my_circ_buf, test);
    circ_bbuf_push(&my_circ_buf, test);
    circ_bbuf_push(&my_circ_buf, test);
    circ_bbuf_push(&my_circ_buf, test);

    /*if (circ_bbuf_pop(&my_circ_buf, &out_data)) {
        printf("CB is empty\n");
    }*/
    circ_bbuf_pop(&my_circ_buf, &out_data);
    printf("Pop:  0x%x\n", out_data);
    circ_bbuf_pop(&my_circ_buf, &out_data);
    printf("Pop:  0x%x\n", out_data);
    circ_bbuf_pop(&my_circ_buf, &out_data);
    printf("Pop:  0x%x\n", out_data);

    if (circ_bbuf_push(&my_circ_buf, in_data)) {
        printf("Out of space in CB\n");
    }
    if (circ_bbuf_push(&my_circ_buf, in_data)) {
        printf("Out of space in CB\n");
    }
    if (circ_bbuf_push(&my_circ_buf, in_data)) {
        printf("Out of space in CB\n");
    }
    //printf("Push: 0x%x\n", in_data);
    
}


