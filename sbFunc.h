#pragma once
#include <stdlib.h>
#include <time.h>
#include <assert.h>

typedef struct sudokuBuildFunc
{
	void (*swapVertical) (int(*)[9], int, int);
	void (*swapHorizontal) (int(*)[9], int, int);
	void (*swap3LHorizontal) (int(*)[9], int, int);
	void (*swap3LVertical) (int(*)[9], int, int);
	void (*swapNum) (int(*)[9], int, int);
}sbFunc;

typedef struct sudokuManageFunc
{
	void (*makeHole) (int(*)[9], int);
	void (*makeGraph) (int(*)[9], char(*)[9]);
	void (*makeBitMask) (int(*)[9], int(*)[9], int, int);
}smFunc;

typedef struct sudokuFunc
{
	sbFunc Build;
	smFunc Manage;
	void (*sbFunc_Init)(sbFunc*);
	void (*smFunc_Init)(smFunc*);
}sFunc;

typedef enum _bool { false, true } bool;

void swapVerticalLine(int arr[9][9], int a, int b);
void swapHorizontalLine(int arr[9][9], int a, int b);
void swapHorizontal3Line(int arr[9][9], int a, int b);
void swapVertical3Line(int arr[9][9], int a, int b);
void swapNum(int arr[9][9], int a, int b);

void makeRandomHole(int arr[9][9], int a);
void setGraphic(int arr[9][9], char graph[9][9]);
void makeBitMask(int arr[9][9], int mask[9][9], int a, int b);

void sbFunc_Initializer(sbFunc *sb);
void smFunc_Initializer(smFunc* sb);
void sFunc_Init(sFunc* sfnc);