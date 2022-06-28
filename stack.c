#include "stack.h"

int pop(IntStack* stack)
{
	if (stack->top >= 0)
	{
		int tv = stack->data[stack->top];
		stack->top--;
		return tv;
	}
	return 0;
}
void push(IntStack* stack, int p)
{
	if (stack->top < stack->max - 1)
	{
		stack->top++;
		stack->data[stack->top] = p;
	}
	else
	{
		stack->max = stack->max * 2;
		int tmp = stack->data;
		if (NULL == (stack->data = (int*)realloc(stack->data, stack->max * sizeof(int))))
		{
			free(tmp);
			exit(1);
		}
		push(stack, p);
	}
}
void init(IntStack* stack, int size)
{
	stack->top = -1;
	stack->data = (int*)malloc(size * sizeof(int));
	stack->max = size;
}
void stackFuncInit(IntStack* intstack)
{
	intstack->init = init;
	intstack->pop = pop;
	intstack->push = push;
}