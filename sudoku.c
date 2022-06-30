#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "sbFunc.h"
#include "sdk.h"


//�۾� �� ����
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
	int hint;
}Setting;

//���ο� ��������� �Լ��� ���� �� ���� ��
Setting setting;

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

//����� �Ҷ� �Ѵ� ��
//#define DEBUG
//#define DEBUG2

FILE* file = NULL;

//��ġ �۰� ������ �Լ��� �и�
sFunc SFunc;

int sdk()
{
	if (0 != fopen_s(&file, "C:\\Users\\USER\\AppData\\Local\\FGSM\\data.txt", "r")) exit(1);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	bool tmp = false;

	setting.seed = (int)time(NULL);

	fscanf_s(file, "%d %d", &setting.diff, &setting.hint);
	if (setting.diff == NULL)
	{
		setting.diff = 4;
		setting.hint = 0;
		fclose(file);
		if (0 != fopen_s(&file, "C:\\Users\\USER\\AppData\\Local\\FGSM\\data.txt", "w")) exit(1);
		fprintf_s(file, "%d %d", setting.diff, setting.hint);
	}
	fclose(file);

	sFunc_Init(&SFunc);

	system("mode con cols=80 lines=20 | title ������");

#ifdef DEBUG
	COORD buffersize = { 150, 20000 };
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), buffersize);
#endif

	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	//��¿�
	while (1)
	{
		for (int i = 0; i < 80; i += 2)
		{
			for (int j = 0; j < 20; j++)
			{
				gotoxy(i, j);
				if (i == 0 || i == 78 || j == 0 || j == 19) printf("��");
				else printf("  ");
			}
		}
		gotoxy(20, 10);
		printf("������");
		gotoxy(20, 11);
		printf("������");
		gotoxy(20, 12);
		printf("������");
		int y = 0;
		char in;
		while (1)
		{
			gotoxy(20, 10 + y);
			printf("��");
			while (!_kbhit());//Ŀ���� ������ �������� �ʰ� ��
			if (_kbhit()) {
				in = _getch();
				if (in == -32)
				{
					in = _getch();
					switch (in) {
					case DOWN:
						if (y < 2)
						{
							y++;
							gotoxy(20, 10 + y - 1);
							printf("��");
						}
						break;
					case UP:
						if (y > 0)
						{
							y--;
							gotoxy(20, 10 + y + 1);
							printf("��");
						}
						break;
					default: break;
					}
				}
				else
				{
					switch (in)
					{
					case 13: tmp = true;
					}
				}
				if (tmp)
				{
					switch (y)
					{
					case 0:
					{
						system("cls");
						ingame();
						break;
					}
					case 1:
					{
						system("cls");
						settingScreen();
						system("cls");
						break;
					}
					case 2:
					{
						return 0;
					}
					default: break;
					}
					tmp = false;
					break;
				}
			}
		}
	}
	fclose(file);
	return 0;
}

void settingScreen()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	int seed = time(NULL);
	bool tmp = false;
	for (int i = 0; i < 80; i += 2)
	{
		for (int j = 0; j < 20; j++)
		{
			gotoxy(i, j);
			if (i == 0 || i == 78 || j == 0 || j == 19) printf("��");
			else printf(" ");
		}
	}
	gotoxy(2, 1);
	printf("���õ�");
	gotoxy(2, 2);
	printf("�����̵�");
	gotoxy(2, 3);
	printf("���ڵ� �޸� Ȱ��ȭ");
	gotoxy(44, 1);
	printf("���̵� �� ������");
	gotoxy(44, 3);
	printf("�� ���� �������� ������ ����");
	gotoxy(44, 4);
	printf("1 : 4  2 ~ 5 : 5  6 : 6");
	gotoxy(44, 6);
	printf("4 ~ 6 : �������� ������ ������");
	gotoxy(44, 8);
	printf("5 ~ 6 : Ʋ�� ���� ���� �� ����");
	int y = 0;
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
			printf("������ ������ ���� �õ� ���� : %d", setting.seed);
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
			printf("�������� ���̵� ����(1 ~ 6) : %d", setting.diff);
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
			printf("��� �� ������ ������ �� ������ ����� ���� �ڵ����� �޸� : %s", setting.hint == 0 ? "False" : "True");
			break;
		}
		default:break;
		}

		gotoxy(2, 1 + y);
		printf("��");
		while (!_kbhit());
		if (_kbhit()) {
			in = _getch();
			if (in == -32)
			{
				in = _getch();
				switch (in) {
				case DOWN:
					if (y < 2)
					{
						y++;
						gotoxy(2, 1 + y - 1);
						printf("��");
					}
					break;
				case UP:
					if (y > 0)
					{
						y--;
						gotoxy(2, 1 + y + 1);
						printf("��");
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
						printf("������ ������ ���� �õ� ���� : ");
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
						printf("�������� ���̵� ����(1 ~ 6) : ");
						while (1)
						{
							gotoxy(32, 18);
							for (int i = 32; i < 76; i++)
							{
								printf(" ");
							}
							gotoxy(32, 18);
							scanf_s("%d", &a);
							if (a <= 6 && a > 0)
							{
								setting.diff = a;
								if (0 != fopen_s(&file, "C:\\Users\\USER\\AppData\\Local\\FGSM\\data.txt", "w")) exit(1);
								fprintf_s(file, "%d %d", setting.diff, setting.hint);
								fclose(file);
								break;
							}
							else
							{
								gotoxy(32, 18);
								printf("���� �ʰ�");
								Sleep(500);
							}
						}
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
						printf("��� �� ������ ������ �� ������ ����� ���� �ڵ����� �޸� : ");
						while (1)
						{
							gotoxy(62, 18);
							for (int i = 62; i < 76; i++)
							{
								printf(" ");
							}
							gotoxy(62, 18);
							scanf_s("%s", s, 6);
							int t = strlen(s);
							for (int i = 0; i < 6; i++)
							{
								if (s[i] >= 65 && s[i] <= 96) s[i] += 32;
							}
							if (!strcmp(s, "true"))
							{
								setting.hint = 1;
								if (0 != fopen_s(&file, "C:\\Users\\USER\\AppData\\Local\\FGSM\\data.txt", "w")) exit(1);
								fprintf_s(file, "%d %d", setting.diff, setting.hint);
								fclose(file);
								break;
							}
							else if (!strcmp(s, "false"))
							{
								setting.hint = 0;
								if (0 != fopen_s(&file, "C:\\Users\\USER\\AppData\\Local\\FGSM\\data.txt", "w")) exit(1);
								fprintf_s(file, "%d %d", setting.diff, setting.hint);
								fclose(file);
								break;
							}
							else
							{
								gotoxy(62, 18);
								printf("�߸��� �Է�");
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
	gotoxy(35, 8);
	printf("������");
	unsigned int seed = ((((setting.seed ^ (setting.diff << 11)) ^ setting.seed >> 4)) << 6) ^ (((setting.diff << 4) ^ (setting.seed >> 2)) ^ setting.seed);
	if (seed == 0)
	{
		seed = setting.seed ^ 8008;
		seed = 2314 << ((seed ^ seed) >> 2);
	}
	srand(seed);//�̰ɷ� ������ ����

	int sudoku[9][9] = { 0, }, solve[9][9] = { 0, }, temp[9][9] = { 0, }, mask[9][9] = { 0, }, memo[9][9] = { 0, };
	char graph[9][9]; // �ʿ��� �迭��

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

		//��� ������ ����
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
		printf("���\n");
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

		//�� �κп��� �� ��� �������� ����� �� �������� ��ȯ��
		for (int i = 0; i < 20; i++)
		{
			int temp = rand() % 5;
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

		//�������� ���� ���� Ǯ� Ŀ����X ���� Ǯ���� while�� Ż��
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

	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoxy(0, 0);
	printf("�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ��  x =   y =  �� �� �� �� �� �� �� �� �� �� �� ��\n");
	printf("��           ��           ��           ��             ��         �޸�        ��\n");
	printf("��           ��           ��           ��             ��                     ��\n");
	printf("��           ��           ��           ��             �� �� �� �� �� �� �� �� �� �� �� ��\n");
	printf("��           ��           ��           ��\n");
	printf("��           ��           ��           ��\n");
	printf("�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ��\n");
	printf("��           ��           ��           ��\n");
	printf("��           ��           ��           ��             �� �� �� �� �� �� �� �� �� �� �� ��\n");
	printf("��           ��           ��           ��             �� R : �����          ��\n");
	printf("��           ��           ��           ��             �� ESC : �޴�          ��\n");
	printf("��           ��           ��           ��             �� ȭ��ǥ Ű : �̵�    ��\n");
	printf("�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ��             �� ���� : �޸�         ��\n");
	printf("��           ��           ��           ��             �� 0 : ���� �����     ��\n");
	printf("��           ��           ��           ��             �� 1 ~ 9 : ���� ����   ��\n");
	printf("��           ��           ��           ��             ��                     ��\n");
	printf("��           ��           ��           ��             ��                     ��\n");
	printf("��           ��           ��           ��             ��                     ��\n");
	printf("�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ��             �� �� �� �� �� �� �� �� �� �� �� ��\n");
	//�Լ� ������ �� ��ũ�� �ϴ� ���� ���̱� ���� �߰�ȣ�� ����
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

		if (setting.hint)
		{
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					memo[i][j] = mask[i][j];
				}
			}
		}

		while (1)
		{
			gotoxy(38, 0);
			printf("x = %d y = %d", x + 1, y + 1);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
			gotoxy(52, 2);
			printf("                    ");
			gotoxy(52, 2);
			for (int k = 0; k < 9; k++)
			{
				int r = memo[x][y] >> k & 1;
				if (r >= 1)printf("%d ", k + 1);
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			gotoxy(x * 4 + 2, y * 2 + 1);
			if (solve[x][y] == 0) printf("��");
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
						getInput(mask, x, y, solve, in - 48);
					}
					else
					{
						switch (in)
						{
						case 13:
						{
							char in2 = 1;
							gotoxy(2, 19);
							printf("�޸� ���� : ");
							while (in2 != 13)
							{
								in2 = _getche();
								if (in2 >= '1' && in2 <= '9')
								{
									memo[x][y] = memo[x][y] ^ (1 << (in2 - 49));
								}
							}
							gotoxy(2, 19);
							for (int i = 2; i < 78; i++)
							{
								printf(" ");
							}
							break;
						}
						case 27:
						{
							gotoxy(54, 5);
							printf("����  ����  ���");
							int tmpx = 0;
							char tmpin;
							gotoxy(54 + tmpx * 6, 6);
							printf("��");
							while (1)
							{
								if (_kbhit())
								{
									tmpin = _getch();
									if (tmpin == -32)
									{
										tmpin = _getch();
										switch (tmpin)
										{
										case LEFT:
											if (tmpx > 0)
											{
												tmpx--;
												gotoxy(54, 6);
												printf("                ");
												gotoxy(54 + tmpx * 6, 6);
												printf("��");
											}
											break;
										case RIGHT:
											if (tmpx < 2)
											{
												tmpx++;
												gotoxy(54, 6);
												printf("               ");
												gotoxy(54 + tmpx * 6, 6);
												printf("��");
											}
											break;
										default: break;
										}
									}
									else
									{
										if (tmpin == 13)
										{
											switch (tmpx)
											{
											case 0:
												submit(solve, sudoku);
												return 0;
											case 1:
												return 0;
											case 2:
												break;
											}
											break;
										}
									}
								}
							}
							gotoxy(54, 5);
							printf("                ");
							gotoxy(54, 6);
							printf("                ");
							break;
						}
						case '0':
						{
							if (solve[x][y] == 0) break;
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



void submit(int solve[9][9], int sudoku[9][9])
{
	bool b = true;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (solve[i][j] != sudoku[i][j])
			{
				b = false;
			}
		}
	}
	system("cls");
	printf("�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ��\n");
	printf("��       ��       ��       �� ��       ��       ��       ��\n");
	printf("��       ��       ��       �� ��       ��       ��       ��\n");
	printf("��       ��       ��       �� ��       ��       ��       ��\n");
	printf("�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ��\n");
	printf("��       ��       ��       �� ��       ��       ��       ��\n");
	printf("��       ��       ��       �� ��       ��       ��       ��\n");
	printf("��       ��       ��       �� ��       ��       ��       ��\n");
	printf("�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ��\n");
	printf("��       ��       ��       �� ��       ��       ��       ��\n");
	printf("��       ��       ��       �� ��       ��       ��       ��\n");
	printf("��       ��       ��       �� ��       ��       ��       ��\n");
	printf("�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ��\n\n");
	printf("�� �� �� �� �� �� �� �� ��\n");
	printf("��               ��\n");
	printf("�� �� �� �� �� �� �� �� ��\n");
	printf("�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ��\n");
	printf("��                               ��\n");
	printf("�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ��");
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			gotoxy((i + 1)* 2 + (i / 3) * 2, j + 1 + (j / 3));
			if(solve[i][j] != 0)
			printf("%d", solve[i][j]);
			gotoxy((i + 1) * 2 + (i / 3) * 2 + 26, j + 1 + (j / 3));
			if (solve[i][j] != sudoku[i][j])
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
			printf("%d", sudoku[i][j]);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		}
	}
	gotoxy(2, 15);
	if (!b)
		printf("Ʋ�Ƚ��ϴ�");
	else
		printf("�¾ҽ��ϴ�");
	gotoxy(2, 18);
	printf("�õ� : %d  ���̵� : %d", setting.seed, setting.diff);
	gotoxy(2, 13);
	printf("����� ������             ����");
	Sleep(1000);
	char in;
	while(1)
	{
		in = _getch();
		if (in == 13)
		{
			setting.seed = time(NULL);
			return;
		}
	}
}


void getInput(int mask[9][9], int x, int y, int solve[9][9], int in)
{
	in--;
	if (setting.diff < 5)
	{
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
	else
	{
		if (solve[x][y] == 0)
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
}

//�и� ���������� C���� Boolean�� ���� ������ Boolean�� ������ ���ο��� �ۼ�

//Ŀ���� X ���� Ǯ�� ���� ������ ���̻� Ǯ �� ���� �� ��ȯ
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

	/*�� �κ� �ڵ� ����: 
	��Ʈ����ũ�� �о� ������ ����� ���� 1���̸� �ٷ� üũ
	�ƴ� �� �ٸ� ĭ�� �о� 1���� ���� �� ������ üũ
	�ƴ� �� üũ���� �ʰ� �Ѿ,
	81ĭ ���� üũ�� ������ �� Ǯ���� �Ǵ��ϰ� ���� Ż��*/
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


void genBasedOnRand(int arr[9][9], int mask[9][9])
{
	//1~9������ ������ ���� 9*9 �迭�� ä�� �� ������ ��Ģ�� ���� �ʴ� ĭ�� ����
	//�� �� Ǯ� ��Ǯ���� ��Ǯ�� ĭ�� ���� �� ä��� Ǯ�� ������ �ݺ�
	//5ȸ �̻� �õ� �� ���н� ó������

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

		//��������� ��Ʈ����ũ ������� �� �ߺ� �� �� ���� ����� �ֱ⿡�� ���ǰ� �ʹ� ŭ, C++�� �ƴϱ� ������ �������� �����ͼ� ���ۼ�
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