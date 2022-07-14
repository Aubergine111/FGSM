#pragma once
void solveS(int temp[9][9], int mask[9][9]);
void getInput(int mask[9][9], int x, int y, int solve[9][9], int in);
void gotoxy(int x, int y);
void settingScreen();
int ingame();
int sdk();
void genBasedOnRand(int arr[9][9], int mask[9][9]);
void submit(int solve[9][9], int sudoku[9][9]);