#ifndef __MINE_H_
#define __MINE_H_

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable:4996)

#define ROWS 12
#define COLS 12
#define MAX_MINE 20

void game();
void mineput(char mineboard[][COLS], int rows, int cols);
void show(char board[][COLS], int rows, int cols);
int total(char mineboard[][COLS], int x, int y);
void total_itoa(char mineboard[][COLS], char showboard[][COLS], int x, int y);
void LongExplode1(char mineboard[][COLS], char showboard[][COLS], int x, int y);
void LongExplode2(char mineboard[][COLS], char showboard[][COLS], int x, int y);
void LongExplode3(char mineboard[][COLS], char showboard[][COLS], int x, int y);
void LongExplode4(char mineboard[][COLS], char showboard[][COLS], int x, int y);
int play(char mineboard[][COLS], char showboard[][COLS], int rows, int cols/*, int *NoMine*/);



#endif  //__MINE_H_