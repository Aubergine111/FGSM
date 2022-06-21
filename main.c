#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include "sbFunc.h"

enum ColorType {
	BLACK,
	DARKBLUE,
	DARKGREEN,
	DARKSKYBLUE,
	DARKRED,
	DARKPURPLE,
	DARKYELLOW,
	GRAY,
	DARKGRAY,
	BLUE,
	GREEN,
	SKYBLUE,
	RED,
	PURPLE,
	YELLOW,
	WHITE
} COLOR;

typedef struct _setting
{
	unsigned int seed;
	int diff;
	bool hint;
}Setting;

Setting setting;

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
//#define DEBUG
//#define DEBUG2

sFunc SFunc;

bool solveWithoutKnuth(int temp[9][9], int mask[9][9], int sudoku[9][9]);
void checkValidInput(int mask[9][9], int x, int y, int solve[9][9], int in);
void gotoxy(int x, int y);
void settingScreen();

int ingame();

int main()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	bool tmp = false, start = false, set = false;

	setting.seed = (int)time(NULL);
	setting.diff = 5;
	setting.hint = false;
	sFunc_Init(&SFunc);

	while (1)
	{
		for (int i = 0; i < 80; i += 2)
		{
			for (int j = 0; j < 20; j++)
			{
				gotoxy(i, j);
				if (i == 0 || i == 78 || j == 0 || j == 19) printf("■");
				else printf(" ");
			}
		}
		gotoxy(20, 10);
		printf("▷시작");
		gotoxy(20, 11);
		printf("▷설정");
		int x = 0, y = 0;
		char in;
		while (1)
		{
			gotoxy(20, 10 + y);
			printf("▶");
			while (!_kbhit());
			if (_kbhit()) {
				in = _getch();
				if (in == -32)
				{
					in = _getch();
					switch (in) {
					case LEFT:
						if (x > 0)x--;
						break;
					case RIGHT:
						if (x < 8)x++;
						break;
					case DOWN:
						if (y < 1)
						{
							y++;
							gotoxy(20, 10 + y - 1);
							printf("▷");
						}
						break;
					case UP:
						if (y > 0)
						{
							y--;
							gotoxy(20, 10 + y + 1);
							printf("▷");
						}
						break;
					default: break;
					}
				}
				else
				{
					switch (in)
					{
					case 27: return 0;
					case 13: tmp = true;
					}
				}
				if (tmp)
				{
					switch (y)
					{
					case 0: start = true; set = false; break;
					case 1: start = false; set = true; break;
					default: break;
					}
					tmp = false;
				}
				if (start)
				{
					system("cls");
					ingame(&setting);
					start = false;
					return 0;
				}
				if (set)
				{
					system("cls");
					settingScreen(&setting);
					system("cls");
					set = false;
					break;
				}
			}
		}
	}
}

void settingScreen()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	int seed = time(NULL);
	bool tmp = false, start = false, set = false;
	for (int i = 0; i < 80; i += 2)
	{
		for (int j = 0; j < 20; j++)
		{
			gotoxy(i, j);
			if (i == 0 || i == 78 || j == 0 || j == 19) printf("■");
			else printf(" ");
		}
	}
	gotoxy(2, 1);
	printf("▷시드");
	gotoxy(2, 2);
	printf("▷난이도");
	gotoxy(2, 3);
	printf("▷힌트 활성화");
	int x = 0, y = 0;
	char in;
	while (1)
	{
		switch (y)
		{
		case 0:
		{
			gotoxy(2, 18);
			for (int i = 0; i < 76; i++)
			{
				printf(" ");
			}
			gotoxy(2, 18);
			printf("스도쿠 생성에 사용될 시드 설정 : %d", setting.seed);
			break;
		}
		case 1:
		{
			gotoxy(2, 18);
			for (int i = 0; i < 76; i++)
			{
				printf(" ");
			}
			gotoxy(2, 18);
			printf("스도쿠의 난이도 설정 : %d", setting.diff);
			break;
		}
		case 2:
		{
			gotoxy(2, 18);
			for (int i = 0; i < 76; i++)
			{
				printf(" ");
			}
			gotoxy(2, 18);
			printf("사용 시 빈 스도쿠 칸에 들어갈 수 있는 값을 알려줌 : %s", setting.hint == 0 ? "False" : "True");
			break;
		}
		default:break;
		}

		gotoxy(2, 1 + y);
		printf("▶");
		while (!_kbhit());
		if (_kbhit()) {
			in = _getch();
			if (in == -32)
			{
				in = _getch();
				switch (in) {
				case LEFT:
					if (x > 0)x--;
					break;
				case RIGHT:
					if (x < 8)x++;
					break;
				case DOWN:
					if (y < 2)
					{
						y++;
						gotoxy(2, 1 + y - 1);
						printf("▷");
					}
					break;
				case UP:
					if (y > 0)
					{
						y--;
						gotoxy(2, 1 + y + 1);
						printf("▷");
					}
					break;
				default: break;
				}
			}
			else
			{
				switch (in)
				{
				case 27:return;
				}
			}
		}
	}
}

int ingame()
{
	unsigned int seed = setting.seed;
	srand(seed);

	int sudoku[9][9], solve[9][9], temp[9][9], mask[9][9];
	char graph[9][9];
	int status = 0;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			sudoku[i][j] = status % 9 + 1;
			status++;
		}
		status = (status + 3) % 9;
		if (status == 0 || status == 1) status++;
	}

	for (int i = 0; i < 60; i++)
	{
		int temp = rand() % 5;
		int a, b;
		switch (temp)
		{
		case 0:
		{
			int a = rand() % 3;
			int b = rand() % 3;
			if (a > b)
			{
				int temp = a;
				a = b;
				b = temp;
			}
			int c = 3 * (rand() % 3);
			SFunc.Build.swapVertical(sudoku, a + c, b + c);
		}
		case 1:
		{
			int a = rand() % 3;
			int b = rand() % 3;
			if (a > b)
			{
				int temp = a;
				a = b;
				b = temp;
			}
			int c = 3 * (rand() % 3);
			SFunc.Build.swapHorizontal(sudoku, a + c, b + c);
		}
		case 2:
		{
			SFunc.Build.swap3LHorizontal(sudoku, rand() % 3, rand() % 3);
		}
		case 3:
		{
			SFunc.Build.swap3LVertical(sudoku, rand() % 3, rand() % 3);
		}
		case 4:
		{
			SFunc.Build.swapNum(sudoku, (rand() % 9) + 1, (rand() % 9) + 1);
		}
		default: break;
		}
	}

	bool tmp = false;

	while (!tmp)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				solve[i][j] = sudoku[i][j];
			}
		}
		SFunc.Manage.makeHole(solve, 4 + (setting.diff / 2));
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				temp[i][j] = solve[i][j];
			}
		}
		tmp = solveWithoutKnuth(temp, mask, sudoku);
	}
	SFunc.Manage.makeGraph(solve, graph);

#ifdef DEBUG
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			SFunc.Manage.makeBitMask(solve, mask, i, j);
		}
	}
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			printf("%c ", graph[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			printf("%d ", sudoku[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
#ifdef DEBUG2
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int k = 8; k >= 0; --k) {
				int result = mask[i][j] >> k & 1;
				printf("%d", result);
			}
			printf(" ");
		}
		printf("\n");
	}
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			printf("%d ", mask[i][j]);
		}
		printf("\n");
	}
#endif
	bool tmp2 = true;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (sudoku[i][j] != temp[i][j]) tmp2 = false;
		}
	}
	if (tmp2)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				printf("%d ", temp[i][j]);
			}
			printf("\n");
		}
	}
	else
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				for (int k = 8; k >= 0; --k) {
					int result = mask[i][j] >> k & 1;
					printf("%d", result);
				}
				printf(" ");
			}
			printf("\n");
		}
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				printf("%d ", mask[i][j]);
			}
			printf("\n");
		}
	}
#endif
#ifndef DEBUG

	//graphic

	int x = 0, y = 0;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	//함수 편집할 때 스크롤 하는 양을 줄이기 위해 중괄호를 씌움
	{
		for (int i = 0; i < 38; i += 2)
		{
			for (int j = 0; j < 19; j++)
			{
				gotoxy(i, j);
				if (i % 4 == 0 || j % 2 == 0)
				{
					if (i % 12 == 0 || j % 6 == 0)
						printf("■");
					else printf("□");
				}
				else printf("%c", graph[i / 4][j / 2]);
			}
		}

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				temp[i][j] = solve[i][j];
			}
		}

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				SFunc.Manage.makeBitMask(solve, mask, i, j);
			}
		}

		char in;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARKGRAY);

		while (1)
		{
			gotoxy(0, 19);
			for (int k = 0; k < 9; k++) {
				int result = mask[x][y] >> k & 1;
				printf("%d", result);
			}
			gotoxy(x * 4 + 2, y * 2 + 1);
			while (!_kbhit());
			if (_kbhit()) {
				in = _getch();
				if (in == -32)
				{
					in = _getch();
					switch (in) {
					case LEFT:
						if (x > 0)x--;
						break;
					case RIGHT:
						if (x < 8)x++;
						break;
					case DOWN:
						if (y < 8)y++;
						break;
					case UP:
						if (y > 0)y--;
						break;
					default: break;
					}
				}
				else
				{
					if (in >= '1' && in <= '9')
					{
						checkValidInput(mask, x, y, solve, in - 48);
					}
					else
					{
						switch (in)
						{
						case 27: return 0;
						case '0':
						{
							if (temp[x][y] == 0)
							{
								solve[x][y] = 0;
								printf(" ");
								for (int i = 0; i < 9; i++)
								{
									for (int j = 0; j < 9; j++)
									{
										SFunc.Manage.makeBitMask(solve, mask, i, j);
									}
								}
							}
							break;
						}
						case 'r':
						{
							for (int i = 0; i < 9; i++)
							{
								for (int j = 0; j < 9; j++)
								{
									solve[i][j] = temp[i][j];
								}
							}
							for (int i = 0; i < 9; i++)
							{
								for (int j = 0; j < 9; j++)
								{
									SFunc.Manage.makeBitMask(solve, mask, i, j);
								}
							}
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
							for (int i = 2; i < 38; i += 4)
							{
								for (int j = 1; j < 19; j+= 2)
								{
									gotoxy(i, j);
									printf("%c", graph[i / 4][j / 2]);
								}
							}
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
							break;
						}
						default: break;
						}
					}
				}
			}
		}
	}
#endif
	return 0;
}

void checkValidInput(int mask[9][9], int x, int y, int solve[9][9], int in)
{
	in--;
	if ((mask[x][y] & (1 << in)) == (1 << in))
	{
		printf("%d", ++in);
		solve[x][y] = in;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				SFunc.Manage.makeBitMask(solve, mask, i, j);
			}
		}
	}
}

bool solveWithoutKnuth(int temp[9][9], int mask[9][9], int sudoku[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			SFunc.Manage.makeBitMask(temp, mask, i, j);
		}
	}

	bool solving = true;


	/*이 부분 코드 설명: 
	비트마스크를 읽어 가능한 경우의 수가 1개이면 바로 체크
	아닐 시 다른 칸을 읽어 1개로 줄일 수 있으면 체크
	아닐 시 체크하지 않고 넘어감,
	81칸 전부 체크에 실패할 시 풀었다 판단하고 루프 탈출*/
	while (solving)
	{
		solving = false;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				for (int k = 0; k < 9; k++)
				{
					int tempmask = 1 << k;
					if (mask[i][j] == tempmask)
					{
						temp[i][j] = k + 1;
						solving = true;
						break;
					}
				}
				//switch (mask[i][j])
				//{
				//case 0b100000000:
				//{
				//	temp[i][j] = 9;
				//	solving = true;
				//	break;
				//}
				//case 0b010000000:
				//{
				//	temp[i][j] = 8;
				//	solving = true;
				//	break;
				//}
				//case 0b001000000:
				//{
				//	temp[i][j] = 7;
				//	solving = true;
				//	break;
				//}
				//case 0b000100000:
				//{
				//	temp[i][j] = 6;
				//	solving = true;
				//	break;
				//}
				//case 0b000010000:
				//{
				//	temp[i][j] = 5;
				//	solving = true;
				//	break;
				//}
				//case 0b000001000:
				//{
				//	temp[i][j] = 4;
				//	solving = true;
				//	break;
				//}
				//case 0b000000100:
				//{
				//	temp[i][j] = 3;
				//	solving = true;
				//	break;
				//}
				//case 0b000000010:
				//{
				//	temp[i][j] = 2;
				//	solving = true;
				//	break;
				//}
				//case 0b000000001:
				//{
				//	temp[i][j] = 1;
				//	solving = true;
				//	break;
				//}
				//default:break;
				//}
				if (setting.diff >= 4)
				{
					if (solving == false)
					{
						int tempmask = mask[i][j];
						for (int k = 0; k < 9; k++)
						{
							if (i != k)
							{
								tempmask = (tempmask & (~mask[k][j]));
								for (int l = 0; l < 9; l++)
								{
									int tempmask2 = 1 << l;
									if (tempmask == tempmask2)
									{
										temp[i][j] = l + 1;
										solving = true;
										break;
									}
								}
								if (solving) break;
							}
							if (j != k)
							{
								tempmask = (tempmask & (~mask[i][k]));
								for (int l = 0; l < 9; l++)
								{
									int tempmask2 = 1 << l;
									if (tempmask == tempmask2)
									{
										temp[i][j] = l + 1;
										solving = true;
										break;
									}
								}
								if (solving) break;
							}
							int x = (i / 3) * 3;
							int y = (j / 3) * 3;
							for (int l = 0; l < 3; l++)
							{
								for (int m = 0; m < 3; m++)
								{
									if ((x + l == i) && (y + m == j)) break;
									else
									{
										for (int n = 0; n < 9; n++)
										{
											int tempmask2 = 1 << n;
											if (tempmask == tempmask2)
											{
												temp[i][j] = n + 1;
												solving = true;
												break;
											}
										}
										if (solving) break;
									}
								}
								if (solving) break;
							}
						}
					}
				}
			}
		}

		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				SFunc.Manage.makeBitMask(temp, mask, i, j);
	}

	bool tmp = true;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (sudoku[i][j] != temp[i][j]) tmp = false;
		}
	}

	return tmp;
}

void gotoxy(int x, int y)
{
	COORD a = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), a);
}