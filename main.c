#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "sbFunc.h"


//글씨 색 전용
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

//메인에 집어넣으면 함수로 보낼 때 오류 남
Setting setting;

//방향키 입력 전용
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

//디버그 할때 켜는 거
//#define DEBUG
//#define DEBUG2

//덩치 작고 자잘한 함수들 분리
sFunc SFunc;

//스택


//덩치 크거나 메인에 있어야 하는 함수들이나 출력용 함수는 메인 파일에 작성
void solveWithoutKnuth(int temp[9][9], int mask[9][9]);
void checkValidInput(int mask[9][9], int x, int y, int solve[9][9], int in);
void gotoxy(int x, int y);
void settingScreen();
int ingame();
void genBasedOnRand(int arr[9][9], int mask[9][9]);

int main()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	bool tmp = false, start = false, set = false;

	setting.seed = (int)time(NULL);
	setting.diff = 6;
	setting.hint = false;
	sFunc_Init(&SFunc);

	system("mode con cols=80 lines=20 | title 스도쿠");

#ifdef DEBUG
	COORD buffersize = { 150, 20000 };
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), buffersize);
#endif

	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	//출력용
	while (1)
	{
		for (int i = 0; i < 80; i += 2)
		{
			for (int j = 0; j < 20; j++)
			{
				gotoxy(i, j);
				if (i == 0 || i == 78 || j == 0 || j == 19) printf("■");
				else printf("  ");
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
			while (!_kbhit());//커서가 켜져도 깜빡이지 않게 함
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
					break;
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
	printf("▷자동 메모 활성화");
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
			printf("스도쿠의 난이도 설정(1 ~ 6) : %d", setting.diff);
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
			printf("사용 시 가능한 경우의 수를 자동으로 메모 : %s", setting.hint == 0 ? "False" : "True");
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
				case 13: 
				{
					switch (y)
					{
					case 0:
					{
						int a;
						gotoxy(2, 18);
						for (int i = 0; i < 76; i++)
						{
							printf(" ");
						}
						gotoxy(2, 18);
						printf("스도쿠 생성에 사용될 시드 설정 : ");
						gotoxy(35, 18);
						scanf_s("%d", &a);
						setting.seed = a;
						break;
					}
					case 1:
					{
						int a;
						gotoxy(2, 18);
						for (int i = 0; i < 76; i++)
						{
							printf(" ");
						}
						gotoxy(2, 18);
						printf("스도쿠의 난이도 설정(1 ~ 5) : ");
						while (1)
						{
							gotoxy(32, 18);
							for (int i = 32; i < 76; i++)
							{
								printf(" ");
							}
							gotoxy(32, 18);
							scanf_s("%d", &a);
							if (a <= 6 && a > 0) break;
							else
							{
								gotoxy(32, 18);
								printf("범위 초과");
								Sleep(500);
							}
						}
						setting.diff = a;
						break;
					}
					case 2:
					{
						char s[6];
						gotoxy(2, 18);
						for (int i = 0; i < 76; i++)
						{
							printf(" ");
						}
						gotoxy(2, 18);
						printf("사용 시 가능한 경우의 수를 자동으로 메모 : ");
						while (1)
						{
							gotoxy(45, 18);
							for (int i = 45; i < 76; i++)
							{
								printf(" ");
							}
							gotoxy(45, 18);
							scanf_s("%s", s, 6);
							int t = strlen(s);
							for (int i = 0; i < 6; i++)
							{
								if (s[i] >= 65 && s[i] <= 96) s[i] += 32;
							}
							if (!strcmp(s, "true"))
							{
								setting.hint = true;
								break;
							}
							else if (!strcmp(s, "false"))
							{
								setting.hint = false;
								break;
							}
							else
							{
								gotoxy(45, 18);
								printf("허용되지 않은 입력");
								Sleep(500);
							}
						}
						break;
					}
					}
				}
				}
			}
		}
	}
}

int ingame()
{
	unsigned int seed = ((((setting.seed ^ (setting.diff << 11)) ^ setting.seed >> 4)) << 6) ^ (((setting.diff << 4) ^ (setting.seed >> 2)) ^ setting.seed);
	if (seed == 0)
	{
		seed = setting.seed ^ 8008;
		seed = 2314 << ((seed ^ seed) >> 2);
	}
	srand(seed);//이걸로 스도쿠 결정

	int sudoku[9][9], solve[9][9], temp[9][9], mask[9][9];
	char graph[9][9]; // 필요한 배열들

	if (setting.diff < 4)
	{
		int status = 0;
		int sarr[9] = { 1,2,3,4,5,6,7,8,9 };
		int rtp = rand() % 50 + 1;
		for (int i = 0; i < rtp; i++)
		{
			int tmpp1 = rand() % 9, tmpp2 = rand() % 9;
			int tmpp3 = sarr[tmpp1];
			sarr[tmpp1] = sarr[tmpp2];
			sarr[tmpp2] = tmpp3;
		}

		//기반 스도쿠 생성
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				sudoku[i][j] = sarr[status % 9];
				status++;
			}
			status = (status + 3) % 9;
			if (status == 0 || status == 1) status++;
		}

#ifdef DEBUG
		printf("기반\n");
		{
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					printf("%d ", sudoku[i][j]);
				}
				printf("\n");
			}
		}
#endif

		//이 부분에서 저 기반 스도쿠를 제대로 된 스도쿠로 변환함
		for (int i = 0; i < 20; i++)
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
				break;
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
				break;
			}
			case 2:
			{
				SFunc.Build.swap3LHorizontal(sudoku, rand() % 3, rand() % 3);
				break;
			}
			case 3:
			{
				SFunc.Build.swap3LVertical(sudoku, rand() % 3, rand() % 3);
				break;
			}
			case 4:
			{
				SFunc.Build.swapNum(sudoku, (rand() % 9) + 1, (rand() % 9) + 1);
				break;
			}
			default: break;
			}
		}

		bool tmp = false;

		//스도쿠에 구멍 내고 풀어서 커누스X 없이 풀리면 while문 탈출
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
			solveWithoutKnuth(temp, mask);
			tmp = true;
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					if (sudoku[i][j] != temp[i][j]) tmp = false;
				}
			}
		}
	}
	else
	{
		bool tmp = false;
		genBasedOnRand(sudoku, mask);
#ifdef DEBUG
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				printf("%d ", sudoku[i][j]);
			}
			printf("\n");
		}
#endif
		while (!tmp)
		{
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					solve[i][j] = sudoku[i][j];
				}
			}
			SFunc.Manage.makeHole(solve, 4 + (setting.diff / 3));
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					temp[i][j] = solve[i][j];
				}
			}
			solveWithoutKnuth(temp, mask);
			tmp = true;
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					if (sudoku[i][j] != temp[i][j]) tmp = false;
				}
			}

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
					printf("%d ", temp[i][j]);
				}
				printf("\n");
			}
#endif
		}
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
	exit(0);
#endif
#ifndef DEBUG

	//graphic

	int x = 0, y = 0;

	gotoxy(0, 0);
	printf("┌ ─ ─ ─ ─ ─ ┬ ─ ─ ─ ─ ─ ┬ ─ ─ ─ ─ ─ ┐ x = %d y = %d ┌ ─ ─ ─ ─ ─ ─ ─ ─ ┐\n", x + 1, y + 1);
	printf("│           │           │           │             │                 │\n");
	printf("│           │           │           │             │                 │\n");
	printf("│           │           │           │             └ ─ ─ ─ ─ ─ ─ ─ ─ ┘\n");
	printf("│           │           │           │\n");
	printf("│           │           │           │\n");
	printf("├ ─ ─ ─ ─ ─ ┼ ─ ─ ─ ─ ─ ┼ ─ ─ ─ ─ ─ ┤\n");
	printf("│           │           │           │\n");
	printf("│           │           │           │\n");
	printf("│           │           │           │\n");
	printf("│           │           │           │\n");
	printf("│           │           │           │\n");
	printf("├ ─ ─ ─ ─ ─ ┼ ─ ─ ─ ─ ─ ┼ ─ ─ ─ ─ ─ ┤\n");
	printf("│           │           │           │\n");
	printf("│           │           │           │\n");
	printf("│           │           │           │\n");
	printf("│           │           │           │\n");
	printf("│           │           │           │\n");
	printf("└ ─ ─ ─ ─ ─ ┴ ─ ─ ─ ─ ─ ┴ ─ ─ ─ ─ ─ ┘\n");
	//함수 편집할 때 스크롤 하는 양을 줄이기 위해 중괄호를 씌움
	{
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

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				gotoxy(i * 4 + 2, j * 2 + 1);
				printf(" ");
				gotoxy(i * 4 + 2, j * 2 + 1);
				printf("%c", graph[i][j]);
			}
		}

		while (1)
		{
			gotoxy(38, 0);
			printf("x = %d y = %d", x + 1, y + 1);
			if (setting.hint)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARKGRAY);
				gotoxy(0, 19);
				for (int k = 0; k < 9; k++) {
					int result = mask[x][y] >> k & 1;
					printf("%d", result);
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			}
			gotoxy(x * 4 + 2, y * 2 + 1);
			if (solve[x][y] == 0) printf("□");
			while (!_kbhit());
			if (_kbhit()) {
				in = _getch();
				if (in == -32)
				{
					in = _getch();
					switch (in) {
					case LEFT:
						if (x > 0)x--;
						gotoxy(x * 4 + 6, y * 2 + 1);
						if (solve[x + 1][y] == 0)
						printf("  ");
						break;
					case RIGHT:
						if (x < 8)x++;
						gotoxy(x * 4 - 2, y * 2 + 1);
						if (solve[x - 1][y] == 0)
						printf("  ");
						break;
					case DOWN:
						if (y < 8)y++;
						gotoxy(x * 4 + 2, y * 2 - 1);
						if (solve[x][y - 1] == 0)
						printf("  ");
						break;
					case UP:
						if (y > 0)y--;
						gotoxy(x * 4 + 2, y * 2 + 3);
						if(solve[x][y + 1] == 0)
						printf("  ");
						break;
					default: break;
					}
				}
				else
				{
					if (in >= '1' && in <= '9')
					{
						gotoxy(x * 4 + 2, y * 2 + 1);
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
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
							for (int i = 2; i < 38; i += 4)
							{
								for (int j = 1; j < 19; j+= 2)
								{
									gotoxy(i, j);
									printf("%c", graph[i / 4][j / 2]);
								}
							}
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARKGRAY);
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
		printf("  ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARKGRAY);
		gotoxy(x * 4 + 2, y * 2 + 1);
		printf("%d", ++in);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
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

//분리 가능하지만 C에는 Boolean이 없기 때문에 Boolean을 만들어둔 메인에서 작성

//커누스 X 없이 풀고 찍지 않으면 더이상 풀 수 없을 때 반환
void solveWithoutKnuth(int temp[9][9], int mask[9][9])
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
#ifdef DEBUG2
		printf("\n");
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				printf("%d ", temp[i][j]);
			}
			printf("\n");
		}
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
		if (setting.diff > 5)
			Sleep(200);
#endif
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
						for (int i = 0; i < 9; i++)
							for (int j = 0; j < 9; j++)
								SFunc.Manage.makeBitMask(temp, mask, i, j);
						break;
					}
				}
			}
		}
	}
}

//출력용이라 메인에 작성
void gotoxy(int x, int y)
{
	COORD a = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), a);
}

void genBasedOnRand(int arr[9][9], int mask[9][9])
{
	//1~9까지의 랜덤한 수로 9*9 배열을 채운 뒤 스도쿠 규칙에 맞지 않는 칸을 날림
	//그 뒤 풀어서 안풀리면 안풀린 칸에 임의 수 채우고 풀릴 때까지 반복
	//5회 이상 시도 후 실패시 처음으로

	bool fail = true;

	while (fail)
	{
		int status = 0;
		int sarr[9] = { 1,2,3,4,5,6,7,8,9 };

		for (int i = 0; i < 50; i++)
		{
			int tmpp1 = (rand() / 9) % 9, tmpp2 = (rand() / 9) % 9;
			int tmpp3 = sarr[tmpp1];
			sarr[tmpp1] = sarr[tmpp2];
			sarr[tmpp2] = tmpp3;
		}

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				arr[i][j] = sarr[j];
			}
			for (int i = 0; i < 20; i++)
			{
				int tmpp1 = (rand() / 9) % 9, tmpp2 = (rand() / 9) % 9;
				int tmpp3 = sarr[tmpp1];
				sarr[tmpp1] = sarr[tmpp2];
				sarr[tmpp2] = tmpp3;
			}
		}

		//헤더파일의 비트마스크 생성기는 값 중복 시 값 삭제 기능을 넣기에는 부피가 너무 큼, C++이 아니기 때문에 메인으로 가져와서 재작성
		for (int a = 0; a < 9; a++)
		{
			for (int b = 0; b < 9; b++)
			{
				for (int i = 0; i < 9; i++)
				{
					if (i == a || arr[i][b] == 0) continue;
					if (arr[i][b] == arr[a][b])
					{
						arr[a][b] = 0;
						break;
					}
				}
				for (int i = 0; i < 9; i++)
				{
					if (i == b || arr[a][i] == 0) continue;
					if (arr[a][i] == arr[a][b])
					{
						arr[a][b] = 0;
						break;
					}
				}
				int x = (a / 3) * 3;
				int y = (b / 3) * 3;
				assert(x < 7 && y < 7 && x >= 0 && y >= 0);
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						if (((x + i == a) && (y + j == b)) || arr[a][b] == 0) continue;
						if (arr[x + i][y + j] == arr[a][b])
						{
							arr[a][b] = 0;
							break;
						}
					}
					if (arr[a][b] == 0) break;
				}
			}
		}
		fail = false;
		solveWithoutKnuth(arr, mask);
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (arr[i][j] == 0) fail = true;
			}
		}
	}
}