#include "sbFunc.h"

void swapVerticalLine(int arr[9][9], int a, int b)
{
	if (a == b) return;
	int temp;
	for (int i = 0; i < 9; i++)
	{
		temp = arr[a][i];
		arr[a][i] = arr[b][i];
		arr[b][i] = temp;
	}
}

void swapHorizontalLine(int arr[9][9], int a, int b)
{
	if (a == b) return;
	int temp;
	for (int i = 0; i < 9; i++)
	{
		temp = arr[i][a];
		arr[i][a] = arr[i][b];
		arr[i][b] = temp;
	}
}

void swapHorizontal3Line(int arr[9][9], int a, int b)
{
	if (a == b) return;
	int temp, line1 = 3 * a, line2 = 3 * b;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			temp = arr[line1 + i][j];
			arr[line1 + i][j] = arr[line2 + i][j];
			arr[line2 + i][j] = temp;
		}
	}
}

void swapVertical3Line(int arr[9][9], int a, int b)
{
	if (a == b) return;
	int temp, line1 = 3 * a, line2 = 3 * b;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			temp = arr[j][line1 + i];
			arr[j][line1 + i] = arr[j][line2 + i];
			arr[j][line2 + i] = temp;
		}
	}
}

//swap a and b in sudoku
void swapNum(int arr[9][9], int a, int b)
{
	if (a == b) return;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (arr[i][j] == a) arr[i][j] = b;
			else if (arr[i][j] == b) arr[i][j] = a;
		}
	}
}

//make hole
void makeRandomHole(int arr[9][9], int a)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < a; j++)
		{
			int temp = rand() % 9;
			while (1)
			{
				if (arr[i][temp] != 0)
				{
					arr[i][temp] = 0;
					break;
				}
				else
					temp = rand() % 9;
			}
		}
	}
}

//make int type sudoku array to char type sudoky graphic
void setGraphic(int arr[9][9], char graph[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (arr[i][j] != 0)graph[i][j] = arr[i][j] + 48;
			else graph[i][j] = ' ';
		}
	}
}

//return bitmask
void makeBitMask(int arr[9][9], int mask[9][9], int a, int b)
{
	if (arr[a][b] != 0)
	{
		mask[a][b] = 0;
		return;
	}
	int bitmask = 0x1ff;
	for (int i = 0; i < 9; i++)
	{
		if (arr[i][b] != 0)
		{
			int temp = ~(1 << (arr[i][b] - 1));
			bitmask = bitmask & temp;
		}
	}
	for (int i = 0; i < 9; i++)
	{
		if (arr[a][i] != 0)
		{
			int temp = ~(1 << (arr[a][i] - 1));
			bitmask = bitmask & temp;
		}
	}
	int x = (a / 3) * 3;
	int y = (b / 3) * 3;
	assert(x < 7 && y < 7 && x >= 0 && y >= 0);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (arr[x + i][y + j] != 0)
			{
				int temp = ~(1 << (arr[x + i][y + j] - 1));
				bitmask = bitmask & temp;
			}
		}
	}
	mask[a][b] = bitmask;
}

void sbFunc_Initializer(sbFunc* sb)
{
	sb->swapVertical = swapVerticalLine;
	sb->swapHorizontal = swapHorizontalLine;
	sb->swap3LHorizontal = swapHorizontal3Line;
	sb->swap3LVertical = swapVertical3Line;
	sb->swapNum = swapNum;
}

void smFunc_Initializer(smFunc* sm)
{
	sm->makeHole = makeRandomHole;
	sm->makeGraph = setGraphic;
	sm->makeBitMask = makeBitMask;
}

void sFunc_Init(sFunc* sfnc)
{
	sfnc->sbFunc_Init = sbFunc_Initializer;
	sfnc->smFunc_Init = smFunc_Initializer;
	sfnc->sbFunc_Init(&sfnc->Build);
	sfnc->smFunc_Init(&sfnc->Manage);
}