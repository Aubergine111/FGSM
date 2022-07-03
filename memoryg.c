#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>	
#include <windows.h>	// sleep함수 사용하기 위한 헤더파일
#include<mmsystem.h>	// playsound 함수 
#pragma comment(lib,"winmm.lib")
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

	int score = 0;		// 최종점수
	int hp = 5;			// 체력
	char a[5];			// 랜덤으로 입력된 숫자, 문자 5개 값이 넣어짐
	char ans1;			//	사용자가 답을 입력
	int i, j;			// 배열의 i,j번째 원소를 부를때 사용,for문도 사용
	int y_s = -3;		// ? 
	int block = 0;		// 콘솔창에서 랜덤으로 입력된 숫자, 문자 위치 지정하기 위한 변수
	int cnt = 0;		// 정답횟수 지정
	int repeat = 3;		// ? 
	int st = 3000;		// 3초기다림
	char user;			// 사용자가 게임을 시작할건지 대답을 입력받음
	char* word[5];		// 내가 지정한 단어 5값 저장
	char* w_ans[6];		// 사용자가 내가 지정한 단어 값을 입력하기 위한 변수
	bool correct = true;	// correct 값에 1저장

	printf("Memory Game에 오신걸 환영한다. ^_^\n");
	Sleep(2000);
	printf("\n이 게임은 당신의 기억력을 테스트하는 게임입니다\n");
	Sleep(2000);
	printf("\n화면에 나오는 숫자,문자들을 잘 보고 콘솔창에 입력 해 주세요.\n");
	Sleep(2000);
	setcolor(YELLOW);
	printf("\n정답을 입력하실때는 꼭 왼쪽에 출력된 숫자,문자들부터 차례로 입력 해 주세요.\n");
	Sleep(2000);
	setcolor(WHITE);
	printf("\n별은 목숨을 뜻합니다.\n");
	Sleep(2000);
	printf("\n문제를 틀릴때 마다 별의 갯수가 1개씩 줄어듭니다.\n");
	Sleep(3000);
	printf("\n최대한 많은 문제를 맞춰서 1등에게만 주어지는 왕관을 획득하십시요.\n");
	Sleep(2000);
	setcolor(YELLOW);
	printf("\n게임을 시작하고 싶으시면 \'Y\'를 입력해주세요 : ");
	scanf("%c", &user);
	Sleep(1000);
	setcolor(WHITE);
	system("cls");

	if (user == 'Y' || user == 'y')		// 사용자가 y를 입력했을경우
	{
		printf("게임을 시작합니다!!\n");
		Sleep(1000);					// 1초기다림
		setcolor(YELLOW);				// 폰트 색 노랑색 변경
		printf("\n~Good Luck~");
		Sleep(3000);
		setcolor(WHITE);
		system("cls");					// 콘솔창 비우기
		for (i = 3; i > 0; i--)
		{
			printf("\n%d초 후에 시작!\n\n", i);	// 3초후 시작
			Sleep(1000);

		}
		Sleep(1000);					// 1초 쉬었다가
		while (1)			// 무한반복
		{

			block = 0;		// 콘솔창 출력 좌표 처음엔  = 0 ~ 20인 구간에서만 1개의 숫자,단어,문자 출력
			correct = true;
			for (i = 0; i < 5; i++)
			{
				if (cnt > 5)			// 정답횟수가 5보다 크면
				{
					while (gets() != '\n');	// enter 값 만나기 전까지 입력버퍼 지움.
					a[i] = rand() % 94 + 33;	// 숫자 + 문자(알파벳,특수문자)를 랜덤으로 출력
				}
				else							// 그렇지 않으면
					a[i] = rand() % 10 + 48;	// 숫자를 랜덤으로 출력
			}
			//-------------------------------------------------------------------
			if (cnt >= 2 && cnt < 5)		// 정답횟수가 2보다 크거나 같으면서 5보다 작을경우
			{
				for (i = 0; i < 5; i++)		// word[i]번째 있는 단어를 순서대로 출력
				{
					word[i] = "apple";

				}
			}
			system("cls");				// 콘솔창 비우기
			life(score, hp);			// 점수 목숨 불러오기

			if (cnt < 2 || cnt >= 5)	// 정답횟수가 2보다 작거나 5보다 크거나 같을경우
			{
				for (i = 0; i < 5; i++)	// 랜덤숫자를 5번 출력
				{
					gotoxy(rand() % 20 + block, rand() % +26 + 4);		// x,y위치를 랜덤으로 지정
					setcolor(BLUE);		// 폰트 색 파란색으로 변경
					printf("%c", a[i]);
					block += 20;	// 0 ~ 20 사이에 1개의 숫자, 문자를 출력하고 20을 더해가면서 위치 변경	
				}
				Sleep(st);		// st = 3초를 뜻함
			}
			else if (cnt >= 2 && cnt < 5)	// 정답횟수가 2보다 크거나 같거나, 5보다 작으면
			{
				for (i = 0; i < 5; i++)		// 5번 반복
				{
					gotoxy(rand() % 20 + block, rand() % +26 + 4);	// x,y좌표 랜덤으로 지정
					setcolor(BLUE);		// 폰트 색 파란색으로 변경
					printf("%s", word[i]);	// 내가 저장한 단어들 순서대로 출력
					block += 20;		// 0 ~ 20 사이에 1개의 단어 출력하고 20을 더해가면서 위치 변경
				}
				Sleep(st);		// st = 3초를 뜻함
			}

			for (i = 0; i < 10; i++)	// 10번 반복
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
				if (5 - i == 1) scanf("%c", &ans1);		//  아메코드이다... 사용자가 정답을 입력 (랜덤 숫자 정답 입력)
				else if (cnt >= 2 && cnt < 5)
				{
					scanf("%s", w_ans);	// 단어 정답 입력
				}
				else			scanf("%c ", &ans1);		// 랜덤, 숫자,문자 정답 입력

				if (ans1 != a[i])		// 만약 정답이 아닐경우
				{
					correct = false;	//0을 반환
				}

			}

			if (correct) {		// 정답일 경우 성공출력
				setcolor(YELLOW);
				printf("성공!!!\n");
				setcolor(WHITE);
				score += 50;	// 점수에 50 을 더함
				life(score, hp);	// 점수,체력 불러옴
				cnt++;	// 맞힌횟수 1 증가
			}
			else       // 아닐경우
			{
				setcolor(RED);
				printf("정답이 아닙니다...");		// 출력
				setcolor(WHITE);
				hp--;		//체력 1감소
				life(score, hp);	// 점수,체력 불러옴
			}
			Sleep(1000);		// 1초 쉬었다가
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

void CursorView()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
	cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

