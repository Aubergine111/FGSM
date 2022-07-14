#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>
#include <direct.h>
#include "resource.h"
#include "sdk.h"
#include "memk.h"
#include "nek.h"

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

void gotoxy(int x, int y);
void titledraw();
void menudraw();
void keycontrol();
void textcolor(int color_number);

int main()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	while (1)
	{
		system("mode con cols=100 lines=30 | title = FGSM");
		titledraw();
		menudraw();
		keycontrol();
	}
}


void gotoxy(int x, int y)
{
	COORD Pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void titledraw()
{
	gotoxy(25, 3);
	puts("＠＠＠＠        ＠      ＠          ＠       ＠");

	gotoxy(25, 4);
	puts("＠              ＠      ＠          ＠  ＠   ＠");

	gotoxy(25, 5);
	puts("＠＠＠          ＠      ＠          ＠    ＠ ＠");

	gotoxy(25, 6);
	puts("＠              ＠      ＠          ＠       ＠");

	gotoxy(25, 7);
	puts("＠              ＠＠＠＠＠          ＠       ＠");
	//=====================================================

	gotoxy(26, 10);
	puts("■■■■■■      ■■■■      ■        ■");

	gotoxy(26, 11);
	puts("■                ■            ■ ■  ■ ■");

	gotoxy(26, 12);
	puts("■  ■■■■      ■            ■  ■■  ■");

	gotoxy(26, 13);
	puts("■     ■         ■■■■      ■        ■");

	gotoxy(26, 14);
	puts("■     ■               ■      ■        ■");

	gotoxy(26, 15);
	puts("■■■■■■      ■■■■      ■        ■");
}

void keycontrol()
{
	bool tmp = false;
	static int y = 0;
	char in;
	while (1)
	{
		gotoxy(40, 20 + y * 2);
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
						gotoxy(40, 20 + (y - 1) * 2);
						printf("  ");
					}
					break;
				case UP:
					if (y > -1)
					{
						y--;
						gotoxy(40, 20 + (y + 1) * 2);
						printf("  ");
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
				case -1:
				{
					system("cls");
					nemomain();
					break;
				}
				case 0:
				{
					system("cls");
					memmain();
					system("cls");
					break;
				}
				case 1:
				{
					system("cls");
					sdk();
					system("cls");
					break;
				}
				case 2:
				{
					exit(0);
				}
				default: break;
				}
				tmp = false;
				break;
			}
		}
	}

}

void menudraw()
{
	gotoxy(43, 18);
	printf("- 네모네모로직 -");
	gotoxy(43, 20);
	printf("-  메모리 게임 -");
	gotoxy(43, 22);
	printf("-    스도쿠    - ");
	gotoxy(43, 24);
	printf("-     종료     -");



}

void textcolor(int color_number)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);

}