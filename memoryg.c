#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>	
#include <windows.h>	// sleep함수 사용하기 위한 헤더파일
#include <conio.h>
#include <time.h>
#include <stdbool.h>		// 불 대수
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
	system("mode con cols=100 lines=30 | title = 게임제목");		// 콘솔창 크키 조절

	char user;			// 사용자가 게임을 시작할건지 대답을 입력받음

	printf("Memory Game에 오신걸 환영한다. ^_^\n");
	Sleep(2000);
	printf("\n이 게임은 당신의 기억력을 테스트하는 게임입니다\n");
	Sleep(2000);
	printf("\n화면에 나오는 숫자,문자들을 잘 보고 콘솔창에 입력 해 주세요.\n");
	Sleep(2000);
	setcolor(YELLOW);
	printf("\n정답을 입력하실때는 꼭 왼쪽에 출력된 숫자, 문자들부터 차례로 입력 해 주세요.\n");
	Sleep(2000);
	setcolor(WHITE);
	printf("\n별은 목숨을 뜻합니다.\n");
	Sleep(2000);
	printf("\n문제를 틀릴때 마다 별의 갯수가 1개씩 줄어듭니다.\n");
	Sleep(3000);
	printf("\n1000점을 획득하여 왕관을 획득하십시오.\n");
	Sleep(2000);
	setcolor(YELLOW);
	printf("\n게임을 시작하고 싶으시면 \'Y\'를 입력해주세요 : ");
	while (!_kbhit());
	if (_kbhit) user = _getch();
	setcolor(WHITE);
	system("cls");
	tmpname(user);
}

void setcolor(unsigned text) // 색깔 선택 
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}

void life(int score, int life)
{
	int x = 0;
	gotoxy(42, 1);
	setcolor(YELLOW);
	printf("Score : %d점", score);
	gotoxy(0, 3);
	printf("----------------------------------------------------------------------------------------------------");
	for (int i = life; i > 0; i--) {
		gotoxy(42 + x, 2);
		printf("★");
		x += 2;
	}
}

void GameOver()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
	system("cls");    // 콘솔창 초기화
	system("mode con cols=100 lines=30 | title = 게임제목"); // 콘솔창 크기 조절

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
	printf("아무 키나 눌러서 돌아가기");
}

void CursorView()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
	cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void printcr()
{
	system("cls");    // 콘솔창 초기화
	setcolor(YELLOW);
	gotoxy(48-4, 1);
	printf("★  ★");
	gotoxy(50-4, 2);
	printf("★");
	gotoxy(49-4, 3);
	printf("★★");
	gotoxy(20-4, 5);
	printf("★");
	gotoxy(82-4, 5);
	printf("★");
	gotoxy(47-4, 4);
	printf("★★★★");
	gotoxy(50-4, 5);
	printf("★\n");
	gotoxy(20-4, 6);
	printf("■■                    ■■■■■■■                      ■■\n");
	gotoxy(20-4, 7);
	printf("■  ■                  ■          ■                  ■    ■\n");   // 18
	gotoxy(20-4, 8);
	printf("■     ■            ■                 ■           ■       ■\n");   //12
	gotoxy(20-4, 9);
	printf("■        ■     ■                         ■    ■          ■\n");
	gotoxy(20-4, 10);
	printf("■           ■                                ■             ■\n");
	gotoxy(20-4, 11);
	printf("■                                                            ■\n");
	setcolor(BLUE);
	gotoxy(51-4, 11);
	printf("★");// 별 첫
	setcolor(YELLOW);
	gotoxy(20-4, 12);
	printf("■                                                            ■");
	gotoxy(20-4, 13);
	printf("■                                                            ■");
	gotoxy(20-4, 14);
	printf("■                                                            ■");
	gotoxy(20-4, 15);
	printf("■                                                            ■");
	gotoxy(20-4, 16);
	printf("■                                                            ■");
	gotoxy(20-4, 17);
	printf("■                                                            ■");
	gotoxy(20-4, 18);
	printf("■                                                            ■\n");
	gotoxy(20-4, 19);
	printf("■                                                            ■\n");
	gotoxy(20-4, 20);
	printf("■                                                            ■\n");
	gotoxy(20-4, 21);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ \n");// 40
	setcolor(BLUE);
	gotoxy(46-4, 12);
	printf("★★★★★★");      // 끝 81
	gotoxy(47-4, 13);
	printf("★      ★");
	gotoxy(44-4, 14);
	printf("★★★★★★★★");
	gotoxy(48-4, 15);
	printf("★    ★");
	gotoxy(46-4, 16);
	printf("★★★★★★");
	gotoxy(49-4, 17);
	printf("★\n");
	setcolor(YELLOW);
	gotoxy(0, 22);
	printf("아무 키나 눌러서 돌아가기");
}

void tmpname(char user)
{
	int score = 0;		// 최종점수
	int hp = 5;			// 체력
	char a[5];			// 랜덤으로 입력된 숫자, 문자 5개 값이 넣어짐
	char ans1;			//	사용자가 답을 입력
	int i, j;			// 배열의 i,j번째 원소를 부를때 사용,for문도 사용
	int y_s = -3;		// ? 
	int block = 0;		// 콘솔창에서 랜덤으로 입력된 숫자, 문자 위치 지정하기 위한 변수
	int cnt = 0;		// 정답횟수 지정
	int repeat = 3;		// ? 
	int st = 2000;		// 3초기다림
	char* word[5];		// 내가 지정한 단어 5값 저장
	char* w_ans[6];		// 사용자가 내가 지정한 단어 값을 입력하기 위한 변수
	bool correct = true;	// correct 값에 1저장
	if (user == 'Y' || user == 'y')		// 사용자가 'y'를 입력했울경우
	{
		printf("게임을 시작합니다!!\n");
		Sleep(1000);					// 1초기다림
		setcolor(YELLOW);
		printf("\n~Good Luck~\n");		// 폰트 색 노란색 변경
		Sleep(3000);					// 3초기다림
		setcolor(WHITE);				// 폰트 색 흰색 변경
		system("cls");					// 콘솔창 비우기
		for (i = 3; i > 0; i--)
		{
			printf("\n%d초 후에 시작!\n\n", i);	//  y 입력 받은 후 3초후 시작
			Sleep(1000);

		}
		Sleep(1000);
		while (1)		// 무한반복
		{
			block = 0;
			correct = true;
			for (i = 0; i < 5; i++)
			{
				if (cnt > 10)	// 만약 정답횟수가 10보다 클경우
				{
					a[i] = rand() % 94 + 33;		// 문자 출력
				}
				else
					a[i] = rand() % 10 + 48;		// 그렇지 않으면 숫자출력
			}

			system("cls");							// 콘솔창 비우고
			life(score, hp);						// 목숨,점수 불러오고

			for (i = 0; i < 5; i++)
			{
				gotoxy(rand() % 20 + block, rand() % +26 + 4);	// 랜덤 위치에 숫자,문자 출력
				setcolor(BLUE);									// 폰트 색 파랑
				printf("% c", a[i]);							// 출력
				block += 20;									//x값 20 증가
			}
			Sleep(st);		// st = 3초를 뜻함


			for (i = 0; i < 10; i++)
			{
				for (j = 0; j < 10; j++)
				{
					printf("\r \n ");	// 현재 줄에서 첫 부분으로 이동
				}
			}
			setcolor(WHITE);
			printf("\n정답을 입력하세요 : ");	// 사용자 정답 입력

			rewind(stdin);				// 입력 버퍼 비우기
			for (i = 0; i < 5; i++)
			{
				if (5 - i == 1) scanf("%c", &ans1);		//..? 일때 사용자가 정답 입력하기
				else			scanf("%c ", &ans1);	// 정답 입력하기

				if (ans1 != a[i])						// 만약에 입력한 값이 정답이 아닐때
				{
					correct = false;					// false값을 correct에 대입
				}

			}

			if (correct) {							// correct일 경우에
				setcolor(YELLOW);
				printf("성공!!!\n");					// 성공 출력
				setcolor(WHITE);
				score += 50;						//점수 50점 증가
				life(score, hp);
				cnt++;								// 정답횟수 증가
				if (st > 1000) st -= 100;
			}
			else
			{
				setcolor(RED);
				printf("정답이 아닙니다...");		// 아닐경우 정답이니라고 출력
				setcolor(WHITE);
				hp--;							// 체력 -1	
				life(score, hp);				// 점수, 체력 불러오기
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
	else if (user == 'N' || user == 'n')	// 사용자가 n을 입력했을 경우 종료
	{
		printf("\n왜 들어왔어.. 나가 *_*\n");
		gotoxy(40, 5);
		printf("■          ■");
		gotoxy(40, 6);
		printf("■          ■");
		gotoxy(40, 7);
		printf("■          ■");
		gotoxy(40, 8);
		printf("■          ■");

		gotoxy(46, 9);
		printf("■");
		gotoxy(46, 10);

		printf("■");
		gotoxy(46, 12);
		printf("■");
		gotoxy(44, 13);
		printf("■  ■");
		Sleep(1000);

	}
	else             // 사용자가 y,n 말고 다른 값을 입력했을경우
	{
		printf("\n\'Y\' or \'N\'로만 대답해라...");		// 출력후 종료
		Sleep(1000);
	}
}