#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>	
#include <windows.h>	// sleep�Լ� ����ϱ� ���� �������
#include <conio.h>
#include <time.h>
#include <stdbool.h>		// �� ���
#include "memk.h"

enum {
	BLACK,
	DARK_BLUE,
	DARK_GREEN,
	DARK_SKYBLUE,
	DARK_RED,
	DARK_VOILET,
	DARK_YELLOW,
	GRAY,
	DARK_GRAY,
	BLUE,
	GREEN,
	SKYBLUE,
	RED,
	VIOLET,
	YELLOW,
	WHITE,
};

void memmain()
{
	CursorView();
	play();

}

void play()
{
	srand(time(NULL));
	system("mode con cols=100 lines=30 | title = ��������");		// �ܼ�â ũŰ ����

	char user;			// ����ڰ� ������ �����Ұ��� ����� �Է¹���

	printf("Memory Game�� ���Ű� ȯ���Ѵ�. ^_^\n");
	Sleep(2000);
	printf("\n�� ������ ����� ������ �׽�Ʈ�ϴ� �����Դϴ�\n");
	Sleep(2000);
	printf("\nȭ�鿡 ������ ����,���ڵ��� �� ���� �ܼ�â�� �Է� �� �ּ���.\n");
	Sleep(2000);
	setcolor(YELLOW);
	printf("\n������ �Է��ϽǶ��� �� ���ʿ� ��µ� ����, ���ڵ���� ���ʷ� �Է� �� �ּ���.\n");
	Sleep(2000);
	setcolor(WHITE);
	printf("\n���� ����� ���մϴ�.\n");
	Sleep(2000);
	printf("\n������ Ʋ���� ���� ���� ������ 1���� �پ��ϴ�.\n");
	Sleep(3000);
	printf("\n1000���� ȹ���Ͽ� �հ��� ȹ���Ͻʽÿ�.\n");
	Sleep(2000);
	setcolor(YELLOW);
	printf("\n������ �����ϰ� �����ø� \'Y\'�� �Է����ּ��� : ");
	while (!_kbhit());
	if (_kbhit) user = _getch();
	setcolor(WHITE);
	system("cls");
	tmpname(user);
}

void setcolor(unsigned text) // ���� ���� 
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}

void life(int score, int life)
{
	int x = 0;
	gotoxy(42, 1);
	setcolor(YELLOW);
	printf("Score : %d��", score);
	gotoxy(0, 3);
	printf("----------------------------------------------------------------------------------------------------");
	for (int i = life; i > 0; i--) {
		gotoxy(42 + x, 2);
		printf("��");
		x += 2;
	}
}

void GameOver()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
	system("cls");    // �ܼ�â �ʱ�ȭ
	system("mode con cols=100 lines=30 | title = ��������"); // �ܼ�â ũ�� ����

	gotoxy(20, 9);
	printf("#########  # #          ####    #       ####         ##    ##   #\n");
	gotoxy(20, 10);
	printf("       #   # #        #      #  #     #      #       ##    ##   #\n");
	gotoxy(20, 11);
	printf("      #  ### #          ####    #       ####         ########   #\n");
	gotoxy(20, 12);
	printf("     #     # #                  #         #          ##    ## ###\n");
	gotoxy(20, 13);
	printf("    #      # #           ########         #          ########   #\n");
	gotoxy(20, 14);
	printf("   #       # #           #      #     ########                  #\n");
	gotoxy(20, 15);
	printf("                         ########                               #\n");
	gotoxy(0, 29);
	printf("�ƹ� Ű�� ������ ���ư���");
}

void CursorView()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
	cursorInfo.bVisible = FALSE; //Ŀ�� Visible TRUE(����) FALSE(����)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void printcr()
{
	system("cls");    // �ܼ�â �ʱ�ȭ
	setcolor(YELLOW);
	gotoxy(48-4, 1);
	printf("��  ��");
	gotoxy(50-4, 2);
	printf("��");
	gotoxy(49-4, 3);
	printf("�ڡ�");
	gotoxy(20-4, 5);
	printf("��");
	gotoxy(82-4, 5);
	printf("��");
	gotoxy(47-4, 4);
	printf("�ڡڡڡ�");
	gotoxy(50-4, 5);
	printf("��\n");
	gotoxy(20-4, 6);
	printf("���                    ��������                      ���\n");
	gotoxy(20-4, 7);
	printf("��  ��                  ��          ��                  ��    ��\n");   // 18
	gotoxy(20-4, 8);
	printf("��     ��            ��                 ��           ��       ��\n");   //12
	gotoxy(20-4, 9);
	printf("��        ��     ��                         ��    ��          ��\n");
	gotoxy(20-4, 10);
	printf("��           ��                                ��             ��\n");
	gotoxy(20-4, 11);
	printf("��                                                            ��\n");
	setcolor(BLUE);
	gotoxy(51-4, 11);
	printf("��");// �� ù
	setcolor(YELLOW);
	gotoxy(20-4, 12);
	printf("��                                                            ��");
	gotoxy(20-4, 13);
	printf("��                                                            ��");
	gotoxy(20-4, 14);
	printf("��                                                            ��");
	gotoxy(20-4, 15);
	printf("��                                                            ��");
	gotoxy(20-4, 16);
	printf("��                                                            ��");
	gotoxy(20-4, 17);
	printf("��                                                            ��");
	gotoxy(20-4, 18);
	printf("��                                                            ��\n");
	gotoxy(20-4, 19);
	printf("��                                                            ��\n");
	gotoxy(20-4, 20);
	printf("��                                                            ��\n");
	gotoxy(20-4, 21);
	printf("��������������������������������� \n");// 40
	setcolor(BLUE);
	gotoxy(46-4, 12);
	printf("�ڡڡڡڡڡ�");      // �� 81
	gotoxy(47-4, 13);
	printf("��      ��");
	gotoxy(44-4, 14);
	printf("�ڡڡڡڡڡڡڡ�");
	gotoxy(48-4, 15);
	printf("��    ��");
	gotoxy(46-4, 16);
	printf("�ڡڡڡڡڡ�");
	gotoxy(49-4, 17);
	printf("��\n");
	setcolor(YELLOW);
	gotoxy(0, 22);
	printf("�ƹ� Ű�� ������ ���ư���");
}

void tmpname(char user)
{
	int score = 0;		// ��������
	int hp = 5;			// ü��
	char a[5];			// �������� �Էµ� ����, ���� 5�� ���� �־���
	char ans1;			//	����ڰ� ���� �Է�
	int i, j;			// �迭�� i,j��° ���Ҹ� �θ��� ���,for���� ���
	int y_s = -3;		// ? 
	int block = 0;		// �ܼ�â���� �������� �Էµ� ����, ���� ��ġ �����ϱ� ���� ����
	int cnt = 0;		// ����Ƚ�� ����
	int repeat = 3;		// ? 
	int st = 2000;		// 3�ʱ�ٸ�
	char* word[5];		// ���� ������ �ܾ� 5�� ����
	char* w_ans[6];		// ����ڰ� ���� ������ �ܾ� ���� �Է��ϱ� ���� ����
	bool correct = true;	// correct ���� 1����
	if (user == 'Y' || user == 'y')		// ����ڰ� 'y'�� �Է��߿���
	{
		printf("������ �����մϴ�!!\n");
		Sleep(1000);					// 1�ʱ�ٸ�
		setcolor(YELLOW);
		printf("\n~Good Luck~\n");		// ��Ʈ �� ����� ����
		Sleep(3000);					// 3�ʱ�ٸ�
		setcolor(WHITE);				// ��Ʈ �� ��� ����
		system("cls");					// �ܼ�â ����
		for (i = 3; i > 0; i--)
		{
			printf("\n%d�� �Ŀ� ����!\n\n", i);	//  y �Է� ���� �� 3���� ����
			Sleep(1000);

		}
		Sleep(1000);
		while (1)		// ���ѹݺ�
		{
			block = 0;
			correct = true;
			for (i = 0; i < 5; i++)
			{
				if (cnt > 10)	// ���� ����Ƚ���� 10���� Ŭ���
				{
					a[i] = rand() % 94 + 33;		// ���� ���
				}
				else
					a[i] = rand() % 10 + 48;		// �׷��� ������ �������
			}

			system("cls");							// �ܼ�â ����
			life(score, hp);						// ���,���� �ҷ�����

			for (i = 0; i < 5; i++)
			{
				gotoxy(rand() % 20 + block, rand() % +26 + 4);	// ���� ��ġ�� ����,���� ���
				setcolor(BLUE);									// ��Ʈ �� �Ķ�
				printf("% c", a[i]);							// ���
				block += 20;									//x�� 20 ����
			}
			Sleep(st);		// st = 3�ʸ� ����


			for (i = 0; i < 10; i++)
			{
				for (j = 0; j < 10; j++)
				{
					printf("\r \n ");	// ���� �ٿ��� ù �κ����� �̵�
				}
			}
			setcolor(WHITE);
			printf("\n������ �Է��ϼ��� : ");	// ����� ���� �Է�

			rewind(stdin);				// �Է� ���� ����
			for (i = 0; i < 5; i++)
			{
				if (5 - i == 1) scanf("%c", &ans1);		//..? �϶� ����ڰ� ���� �Է��ϱ�
				else			scanf("%c ", &ans1);	// ���� �Է��ϱ�

				if (ans1 != a[i])						// ���࿡ �Է��� ���� ������ �ƴҶ�
				{
					correct = false;					// false���� correct�� ����
				}

			}

			if (correct) {							// correct�� ��쿡
				setcolor(YELLOW);
				printf("����!!!\n");					// ���� ���
				setcolor(WHITE);
				score += 50;						//���� 50�� ����
				life(score, hp);
				cnt++;								// ����Ƚ�� ����
				if (st > 1000) st -= 100;
			}
			else
			{
				setcolor(RED);
				printf("������ �ƴմϴ�...");		// �ƴҰ�� �����̴϶�� ���
				setcolor(WHITE);
				hp--;							// ü�� -1	
				life(score, hp);				// ����, ü�� �ҷ�����
			}
			Sleep(1000);

			if (score >= 1000)
			{
				printcr();
				while (!_kbhit());
				if (_kbhit) user = _getch();
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
				return;
			}

			if (hp < 1)
			{
				GameOver();
				while (!_kbhit());
				if (_kbhit) user = _getch();
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
				return;
			}
			//==========================================================================================================================================

		}

	}
	else if (user == 'N' || user == 'n')	// ����ڰ� n�� �Է����� ��� ����
	{
		printf("\n�� ���Ծ�.. ���� *_*\n");
		gotoxy(40, 5);
		printf("��          ��");
		gotoxy(40, 6);
		printf("��          ��");
		gotoxy(40, 7);
		printf("��          ��");
		gotoxy(40, 8);
		printf("��          ��");

		gotoxy(46, 9);
		printf("��");
		gotoxy(46, 10);

		printf("��");
		gotoxy(46, 12);
		printf("��");
		gotoxy(44, 13);
		printf("��  ��");
		Sleep(1000);

	}
	else             // ����ڰ� y,n ���� �ٸ� ���� �Է��������
	{
		printf("\n\'Y\' or \'N\'�θ� ����ض�...");		// ����� ����
		Sleep(1000);
	}
}