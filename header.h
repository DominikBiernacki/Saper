#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void clear();

void print(int x, int y, int plansza[x][y][2], int mines);

int neighbours(int x, int y, int plansza[x][y][2], int curx, int cury);

void full(int x, int y, int plansza[x][y][2], int curx, int cury);

int gamecheck(int x, int y, int plansza[x][y][2]);

void logo();

int set_difficulty();

void set_values(int *x, int *y, int *mines, int difficulty);

void board_init(int x, int y, int plansza[x][y][2], int mines);

void main_game(int x, int y, int plansza[x][y][2], int mines, int *game_over);

void endscreen(int game_over);
