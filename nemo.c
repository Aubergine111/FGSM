#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "nek.h"

#define TEST

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

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

int kindcount[16][16];

void nemomain()
{
	system("mode con cols=80 lines=20 | title 네모네모로직");
	bool tmp = false;
	int y = 0;
	char in;
	Setting setting;
	setting.hw = 10;
	setting.type = 0;
	setting.seed = time(NULL);
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
		gotoxy(20, 12);
		printf("▷종료");
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
					case DOWN:
						if (y < 2)
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
						startnemo(&setting);
						system("mode con cols=80 lines=20 | title 네모네모로직");
						setting.seed = time(NULL);
						break;
					}
					case 1:
					{
						system("cls");
						nmsetting(&setting);
						break;
					}
					case 2:
					{
						return;
					}
					default: break;
					}
					tmp = false;
					break;
				}
			}
		}
	}
}

void startnemo(Setting* setting)
{
	bool** arr = NULL, ** solve = NULL, ** mark = NULL;
	ReadNFile(arr, -1, -1);
	int width, height, seed, ***hint;
	width = setting->hw;
	height = setting->hw;
	seed = setting->seed;
	srand(seed);
	system("mode con cols=90 lines=27 | title 임시메세지");
	//동적할당 처리
	{
		arr = (bool**)malloc(height * sizeof(bool*));
		arr[0] = (bool*)malloc(width * height * sizeof(bool));
		for (int i = 1; i < height; i++)
		{
			arr[i] = arr[i - 1] + width;
		}

		solve = (bool**)malloc(height * sizeof(bool*));
		solve[0] = (bool*)malloc(width * height * sizeof(bool));
		for (int i = 1; i < height; i++)
		{
			solve[i] = solve[i - 1] + width;
		}

		mark = (bool**)malloc(height * sizeof(bool*));
		mark[0] = (bool*)malloc(width * height * sizeof(bool));
		for (int i = 1; i < height; i++)
		{
			mark[i] = mark[i - 1] + width;
		}

		hint = (int***)malloc(height * sizeof(int**));
		for (int i = 0; i < height; i++)
		{
			hint[i] = (int**)malloc(width * sizeof(int*));
		}
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				hint[i][j] = (int*)malloc(2 * sizeof(int));
			}
		}

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				arr[i][j] = false;
			}
		}

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				solve[i][j] = false;
			}
		}

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				mark[i][j] = false;
			}
		}

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					hint[i][j][k] = 0;
				}
			}
		}
	}
	if (setting->type == 0)
	{
		for (int i = 0; i < height; i++)
		{
			int c = 0;
			int filln = (rand() % width) + 1;
			if (filln > width)filln = width;
			while (c < filln)
			{
				int j = rand() % width;
				if (!arr[i][j])
				{
					arr[i][j] = true;
					c++;
				}

			}
		}
	}
	else if (setting->type == 1)
	{
		ReadNFile(arr, height, width);
	}
	bool blank = true;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (arr[i][j]) blank = false;
		}
	}
	if (blank && setting->type != 2)
	{
		gotoxy(0, 0);
		printf("지정된 사이즈의 저장된 스도쿠 없음");
		Sleep(1000);
		free(arr[0]);
		free(arr);
		free(solve[0]);
		free(solve);
		free(mark[0]);
		free(mark);

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				free(hint[i][j]);
			}
		}
		for (int i = 0; i < height; i++)
		{
			free(hint[i]);
		}
		free(hint);
		return;
	}

	gethint(arr, hint, height, width);

	const int conint = 72;
	//그래픽
	gotoxy(0, 0);
	{
		printf("┌ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ┐\n");
		for (int i = 0; i < 25; i++)
		{
			printf("│                                                                   │\n");
		}
		printf("└ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ┘");
		gotoxy(48 - width, 16 - width / 2);
		printf("┌ ");
		for (int i = 0; i < width; i++)
		{
			printf("─ ");
		}
		printf("┐\n");
		for (int i = 0; i < height; i++)
		{
			gotoxy(48 - width, 17 - width / 2 + i);
			printf("│ ");
			for (int j = 0; j < width * 2; j++)
			{
				printf(" ");
			}
			printf("│\n");
		}
		gotoxy(48 - width, 17 + (width + 1) / 2);
		printf("└ ");
		for (int i = 0; i < width; i++)
		{
			printf("─ ");
		}
		printf("┘");
	}
	gotoxy(conint - 2, 0);
	printf("┌ ─ ─ ─ ─ ─ ─ ─ ┐");
	for (int i = 1; i < 26; i++)
	{
		gotoxy(conint - 2, i);
		printf("│               │");
	}
	gotoxy(conint - 2, 26);
	printf("└ ─ ─ ─ ─ ─ ─ ─ ┘");
	gotoxy(conint, 1);
	printf("엔터 키");
	gotoxy(conint, 2);
	printf("칸 칠하기");
	gotoxy(conint, 4);
	printf("화살표 키");
	gotoxy(conint, 5);
	printf("이동");
	gotoxy(conint, 7);
	printf("R 키");
	gotoxy(conint, 8);
	printf("리셋");
	gotoxy(conint, 10);
	printf("ESC 키");
	gotoxy(conint, 11);
	printf("메뉴");
	gotoxy(conint, 13);
	printf("0 키");
	gotoxy(conint, 14);
	printf("칸 마킹");
	int y = 0, x = 0;
	char in;
	while (1)
	{
#ifdef DEBUG
		for (int i = 0; i < height; i++)
		{
			gotoxy(50 - width, 17 - width / 2 + i);
			for (int j = 0; j < width; j++)
			{
				if (i == y && j == x) printf("□");
				else if (arr[i][j] == true)
				{
					printf("■");
				}
				else
				{
					printf("  ");
				}
			}
			printf("\n");
		}
#endif
#ifndef DEBUG
		for (int i = 0; i < height; i++)
		{
			gotoxy(50 - width, 17 - width / 2 + i);
			for (int j = 0; j < width; j++)
			{
				if (i == y && j == x) printf("□");
				else if (solve[i][j] == true)
				{
					printf("■");
				}
				else if (mark[i][j])
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
					printf("X ");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
				}
				else
				{
					printf("  ");
				}
			}
			printf("\n");
		}
#endif
		for (int i = 0; i < height; i++)
		{
			gotoxy(30 - width, 17 - width / 2 + i);
			for (int j = 0; hint[i][j][0] != 0; j++)
			{
				printf("%d ", hint[i][j][0]);
			}
		}

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; hint[i][j][1] != 0; j++)
			{
				gotoxy(51 - width + (i * 2), 8 - width / 2 + j);
				printf("%d ", hint[i][j][1]);
			}
		}

		gotoxy(2, 1);
		printf("x = %d, y = %d       ", x, y);
		while (!_kbhit());
		if (_kbhit()) {
			in = _getch();
			if (in == -32)
			{
				in = _getch();
				switch (in) {
				case LEFT:
					if (x > 0)
					{
						x--;
					}
					break;
				case RIGHT:
					if (x < width - 1)
					{
						x++;
					}
					break;
				case DOWN:
					if (y < height - 1)
					{
						y++;
					}
					break;
				case UP:
					if (y > 0)
					{
						y--;
					}
					break;
				default: break;
				}
			}
			switch (in)
			{
			case 13:
			{
				solve[y][x] = !solve[y][x];
				if (mark[y][x]) mark[y][x] = !mark[y][x];
				break;
			}
			case 27:
			{
				gotoxy(2, 3);
				if(setting->type != 2) printf("제출  종료  취소");
				else printf("저장  종료  취소");
				int tmpx = 0;
				char tmpin;
				gotoxy(2 + tmpx * 6, 4);
				printf("▲");
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
									gotoxy(2, 4);
									printf("                ");
									gotoxy(2 + tmpx * 6, 4);
									printf("▲");
								}
								break;
							case RIGHT:
								if (tmpx < 2)
								{
									tmpx++;
									gotoxy(2, 4);
									printf("               ");
									gotoxy(2 + tmpx * 6, 4);
									printf("▲");
								}
								break;
							default: break;
							}
						}
						else if (tmpin == 13)
						{
							switch (tmpx)
							{
							case 0:
								if (setting->type != 2) submitnemo(solve, arr, height, width);
								else SaveNFile(solve, height, width);
								free(arr[0]);
								free(arr);
								free(solve[0]);
								free(solve);
								free(mark[0]);
								free(mark);

								for (int i = 0; i < height; i++)
								{
									for (int j = 0; j < width; j++)
									{
										free(hint[i][j]);
									}
								}
								for (int i = 0; i < height; i++)
								{
									free(hint[i]);
								}
								free(hint);
								return;
							case 1:
								free(arr[0]);
								free(arr);
								free(solve[0]);
								free(solve);
								free(mark[0]);
								free(mark);

								for (int i = 0; i < height; i++)
								{
									for (int j = 0; j < width; j++)
									{
										free(hint[i][j]);
									}
								}
								for (int i = 0; i < height; i++)
								{
									free(hint[i]);
								}
								free(hint);
								return;
							case 2:
								break;
							}
							break;
						}
					}
				}
				gotoxy(2, 3);
				printf("                     ");
				gotoxy(2, 4);
				printf("                     ");
				break;
			}
			case '0':
			{
				if(!solve[y][x]) mark[y][x] = !mark[y][x];
				break;
			}
			case 'r':
			{
				for (int i = 0; i < height; i++)
				{
					for (int j = 0; j < width; j++)
					{
						solve[i][j] = false;
					}
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
				break;
			}
			default: break;
			}
		}
	}
	return;
}

void SaveNFile(bool** arr, int height, int width)
{
	kindcount[height][width]++;
	FILE* fp = NULL;
	fopen_s(&fp, "test.txt", "r+");
	for (int i = 5; i < 16; i++)
	{
		fprintf(fp, "%d %d %d\n", i, i, kindcount[i][i]);
	}
	fprintf(fp, "-1 -1\n");
	fclose(fp);
	if (height < 0) return;
	fopen_s(&fp, "test.txt", "a");
	fprintf(fp, "%d %d\n", height, width);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			fprintf(fp, "%d ", arr[i][j]);
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "\n");
	fclose(fp);
}

void ReadNFile(bool** arr, int height, int width)
{
	FILE* fp = NULL;
	int tmp, inh, inw, tryc = 0, inttryc = 0, indx, indy;
	if (0 != fopen_s(&fp, "test.txt", "r"))
	{
		fopen_s(&fp, "test.txt", "w");
		fclose(fp);
		SaveNFile(arr, -1, -1);
	}
	while(1)
	{
		fscanf_s(fp, "%d %d", &indx, &indy);
		if (indx < 0) break;
		fscanf_s(fp, "%d", &kindcount[indx][indy]);
	}
	if (height == -1)
	{
		fclose(fp);
		return;
	}
	if (kindcount[height][width] == 0) return;
	tryc = rand() % kindcount[height][width];
	while (EOF != fscanf_s(fp, "%d %d", &inh, &inw))
	{
		if (inh == height && inw == width && inttryc >= tryc)
		{
			for (int i = 0; i < inh; i++)
			{
				for (int j = 0; j < inw; j++)
				{
					fscanf_s(fp, "%d", &tmp);
					arr[i][j] = tmp;
				}
			}
			break;
		}
		else
		{
			fseek(fp, (inh * inw * 2) + inh + 1, SEEK_CUR);
			if (inh == height && inw == width) inttryc++;
		}
	}
	fclose(fp);
	//exit(0);
}

void gethint(bool** arr, int*** hint, int height, int width)
{
	int streak = 0, hcount = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (arr[i][j] == false && streak > 0)
			{
				hint[i][hcount][0] = streak;
				streak = 0;
				hcount++;
			}
			else if (arr[i][j])
			{
				streak++;
			}
			else if (arr[i][j] == false)
				streak = 0;
		}
		if(streak != 0) hint[i][hcount][0] = streak;
		hcount = 0;
		streak = 0;
	}
	hcount = 0;
	streak = 0;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (arr[j][i] == false && streak > 0)
			{
				hint[i][hcount][1] = streak;
				streak = 0;
				hcount++;
			}
			else if (arr[j][i])
			{
				streak++;
			}
		}
		if (streak != 0) hint[i][hcount][1] = streak;
		hcount = 0;
		streak = 0;
	}
}

void nmsetting(Setting *setting)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	int seed = time(NULL);
	bool tmp = false;
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
	printf("▷시드 설정");
	gotoxy(2, 2);
	printf("▷세로 길이");
	gotoxy(2, 3);
	printf("▷게임 모드");
	gotoxy(34, 2);
	printf("게임 모드 목록");
	gotoxy(34, 4);
	printf("0 : 랜덤 생성 (패턴 없는 무작위 퍼즐)");
	gotoxy(34, 5);
	printf("1 : 기존 퍼즐 사용 (특정한 그림이 있는 퍼즐)");
	gotoxy(34, 6);
	printf("2 : 퍼즐 제작기");
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
			printf("랜덤 생성시 시드 설정 : %d", setting->seed);
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
			printf("네모네모로직 퍼즐의 크기 : %d", setting->hw);
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
			printf("게임 모드 종류 : %d", setting->type);
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
						printf("랜덤 생성시 시드 설정 : ");
						scanf_s("%d", &a);
						if (a < 0) a *= -1;
						setting->seed = a;
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
						printf("네모네모로직 퍼즐의 크기 : ");
						scanf_s("%d", &a);
						if (a > 15) a = 15;
						if (a < 5) a = 5;
						setting->hw = a;
						break;
					}
					case 2:
					{
						int a;
						gotoxy(2, 18);
						for (int i = 0; i < 76; i++)
						{
							printf(" ");
						}
						gotoxy(2, 18);
						printf("게임 모드 종류 : ");
						scanf_s("%d", &a);
						if (a > 2) a = 2;
						if (a < 0) a = 0;
						setting->type = a;
						break;
					}
					}
				}
				}
			}
		}
	}
}
void submitnemo(bool** submit, bool** arr, int height, int width)
{
	system("cls");

	gotoxy(0, 0);
	printf("┌ ");
	for (int i = 0; i < width; i++)
	{
		printf("─ ");
	}
	printf("┐");
	for (int i = 0; i < height; i++)
	{
		gotoxy(0, 1 + i);
		printf("│");
		gotoxy(width * 2 + 2, 1 + i);
		printf("│");
	}
	gotoxy(0, height + 1);
	printf("└ ");
	for (int i = 0; i < width; i++)
	{
		printf("─ ");
	}
	printf("┘");
	for (int i = 0; i < height; i++)
	{
		gotoxy(2, 1 + i);
		for (int j = 0; j < width; j++)
		{
			if (arr[i][j] != submit[i][j]) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
			if (submit[i][j]) printf("■");
			else printf("  ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		}
	}

	gotoxy(width * 2 + 3, 0);
	printf("┌ ");
	for (int i = 0; i < width; i++)
	{
		printf("─ ");
	}
	printf("┐");
	for (int i = 0; i < height; i++)
	{
		gotoxy(width * 2 + 3, 1 + i);
		printf("│");
		gotoxy(width * 4 + 5, 1 + i);
		printf("│");
	}
	gotoxy(width * 2 + 3, height + 1);
	printf("└ ");
	for (int i = 0; i < width; i++)
	{
		printf("─ ");
	}
	printf("┘");
	for (int i = 0; i < height; i++)
	{
		gotoxy(width * 2 + 5, 1 + i);
		for (int j = 0; j < width; j++)
		{
			if(arr[i][j] != submit[i][j]) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
			if (arr[i][j]) printf("■");
			else printf("  ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		}
	}
	gotoxy(0, height + 3);
	printf("┌ ─ ─ ─ ─ ─ ─ ─ ┐\n");
	printf("│               │\n");
	printf("└ ─ ─ ─ ─ ─ ─ ─ ┘\n");
	gotoxy(4, height + 4);
	bool ans = true;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (submit[i][j] != arr[i][j]) ans = false;
		}
	}
	if (ans) printf("맞았습니다");
	else printf("틀렸습니다");

	char c;
	while (!_kbhit());
	c = _getch();

	return;
}