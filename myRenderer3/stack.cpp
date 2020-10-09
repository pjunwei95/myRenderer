#include "stack.h"
#include <assert.h>
#include "logger.h"

//TODO also dont ever write stuff like "new Array".There's no point anymore.
void testStack()
{
    logmsg("test stack...\n");

    Stack<int>* s = new Stack<int>();
    int num = 1;
    s->push(&num);

    logmsg("peeking value = %d\n", *s->peek());

    s->pop();
    ++num;
    s->push(&num);
    delete s;
}