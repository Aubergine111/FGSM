#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>	
#include <windows.h>	// sleep�Լ� ����ϱ� ���� �������
#include<mmsystem.h>	// playsound �Լ� 
#pragma comment(lib,"winmm.lib")
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

	int score = 0;		// ��������
	int hp = 5;			// ü��
	char a[5];			// �������� �Էµ� ����, ���� 5�� ���� �־���
	char ans1;			//	����ڰ� ���� �Է�
	int i, j;			// �迭�� i,j��° ���Ҹ� �θ��� ���,for���� ���
	int y_s = -3;		// ? 
	int block = 0;		// �ܼ�â���� �������� �Էµ� ����, ���� ��ġ �����ϱ� ���� ����
	int cnt = 0;		// ����Ƚ�� ����
	int repeat = 3;		// ? 
	int st = 3000;		// 3�ʱ�ٸ�
	char user;			// ����ڰ� ������ �����Ұ��� ����� �Է¹���
	char* word[5];		// ���� ������ �ܾ� 5�� ����
	char* w_ans[6];		// ����ڰ� ���� ������ �ܾ� ���� �Է��ϱ� ���� ����
	bool correct = true;	// correct ���� 1����

	printf("Memory Game�� ���Ű� ȯ���Ѵ�. ^_^\n");
	Sleep(2000);
	printf("\n�� ������ ����� ������ �׽�Ʈ�ϴ� �����Դϴ�\n");
	Sleep(2000);
	printf("\nȭ�鿡 ������ ����,���ڵ��� �� ���� �ܼ�â�� �Է� �� �ּ���.\n");
	Sleep(2000);
	setcolor(YELLOW);
	printf("\n������ �Է��ϽǶ��� �� ���ʿ� ��µ� ����,���ڵ���� ���ʷ� �Է� �� �ּ���.\n");
	Sleep(2000);
	setcolor(WHITE);
	printf("\n���� ����� ���մϴ�.\n");
	Sleep(2000);
	printf("\n������ Ʋ���� ���� ���� ������ 1���� �پ��ϴ�.\n");
	Sleep(3000);
	printf("\n�ִ��� ���� ������ ���缭 1��Ը� �־����� �հ��� ȹ���Ͻʽÿ�.\n");
	Sleep(2000);
	setcolor(YELLOW);
	printf("\n������ �����ϰ� �����ø� \'Y\'�� �Է����ּ��� : ");
	scanf("%c", &user);
	Sleep(1000);
	setcolor(WHITE);
	system("cls");

	if (user == 'Y' || user == 'y')		// ����ڰ� y�� �Է��������
	{
		printf("������ �����մϴ�!!\n");
		Sleep(1000);					// 1�ʱ�ٸ�
		setcolor(YELLOW);				// ��Ʈ �� ����� ����
		printf("\n~Good Luck~");
		Sleep(3000);
		setcolor(WHITE);
		system("cls");					// �ܼ�â ����
		for (i = 3; i > 0; i--)
		{
			printf("\n%d�� �Ŀ� ����!\n\n", i);	// 3���� ����
			Sleep(1000);

		}
		Sleep(1000);					// 1�� �����ٰ�
		while (1)			// ���ѹݺ�
		{

			block = 0;		// �ܼ�â ��� ��ǥ ó����  = 0 ~ 20�� ���������� 1���� ����,�ܾ�,���� ���
			correct = true;
			for (i = 0; i < 5; i++)
			{
				if (cnt > 5)			// ����Ƚ���� 5���� ũ��
				{
					while (gets() != '\n');	// enter �� ������ ������ �Է¹��� ����.
					a[i] = rand() % 94 + 33;	// ���� + ����(���ĺ�,Ư������)�� �������� ���
				}
				else							// �׷��� ������
					a[i] = rand() % 10 + 48;	// ���ڸ� �������� ���
			}
			//-------------------------------------------------------------------
			if (cnt >= 2 && cnt < 5)		// ����Ƚ���� 2���� ũ�ų� �����鼭 5���� �������
			{
				for (i = 0; i < 5; i++)		// word[i]��° �ִ� �ܾ ������� ���
				{
					word[i] = "apple";

				}
			}
			system("cls");				// �ܼ�â ����
			life(score, hp);			// ���� ��� �ҷ�����

			if (cnt < 2 || cnt >= 5)	// ����Ƚ���� 2���� �۰ų� 5���� ũ�ų� �������
			{
				for (i = 0; i < 5; i++)	// �������ڸ� 5�� ���
				{
					gotoxy(rand() % 20 + block, rand() % +26 + 4);		// x,y��ġ�� �������� ����
					setcolor(BLUE);		// ��Ʈ �� �Ķ������� ����
					printf("%c", a[i]);
					block += 20;	// 0 ~ 20 ���̿� 1���� ����, ���ڸ� ����ϰ� 20�� ���ذ��鼭 ��ġ ����	
				}
				Sleep(st);		// st = 3�ʸ� ����
			}
			else if (cnt >= 2 && cnt < 5)	// ����Ƚ���� 2���� ũ�ų� ���ų�, 5���� ������
			{
				for (i = 0; i < 5; i++)		// 5�� �ݺ�
				{
					gotoxy(rand() % 20 + block, rand() % +26 + 4);	// x,y��ǥ �������� ����
					setcolor(BLUE);		// ��Ʈ �� �Ķ������� ����
					printf("%s", word[i]);	// ���� ������ �ܾ�� ������� ���
					block += 20;		// 0 ~ 20 ���̿� 1���� �ܾ� ����ϰ� 20�� ���ذ��鼭 ��ġ ����
				}
				Sleep(st);		// st = 3�ʸ� ����
			}

			for (i = 0; i < 10; i++)	// 10�� �ݺ�
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
				if (5 - i == 1) scanf("%c", &ans1);		//  �Ƹ��ڵ��̴�... ����ڰ� ������ �Է� (���� ���� ���� �Է�)
				else if (cnt >= 2 && cnt < 5)
				{
					scanf("%s", w_ans);	// �ܾ� ���� �Է�
				}
				else			scanf("%c ", &ans1);		// ����, ����,���� ���� �Է�

				if (ans1 != a[i])		// ���� ������ �ƴҰ��
				{
					correct = false;	//0�� ��ȯ
				}

			}

			if (correct) {		// ������ ��� �������
				setcolor(YELLOW);
				printf("����!!!\n");
				setcolor(WHITE);
				score += 50;	// ������ 50 �� ����
				life(score, hp);	// ����,ü�� �ҷ���
				cnt++;	// ����Ƚ�� 1 ����
			}
			else       // �ƴҰ��
			{
				setcolor(RED);
				printf("������ �ƴմϴ�...");		// ���
				setcolor(WHITE);
				hp--;		//ü�� 1����
				life(score, hp);	// ����,ü�� �ҷ���
			}
			Sleep(1000);		// 1�� �����ٰ�
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

void CursorView()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
	cursorInfo.bVisible = FALSE; //Ŀ�� Visible TRUE(����) FALSE(����)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

