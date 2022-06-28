#pragma once
#include <stdlib.h>

typedef struct _intstack
{
	int top;
	int* data;
	int max;
	void (*pop)();
	int (*push)(int p);
	void (*init)();
}IntStack;

int pop(IntStack* stack);
void push(IntStack* stack, int p);
void init(IntStack* stack, int size);
void stackFuncInit(IntStack* intstack);