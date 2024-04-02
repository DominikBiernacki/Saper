#include "header.h"


// Prosta funkcja, która pozbywa się wszelakich niechcianych znaków na standardowym wejściu
void clear(){
    while(getchar() != '\n');
}


// Funkcja wyświetlająca obecny stan planszy
void print(int x, int y, int plansza[x][y][2], int mines){
    printf("\n");
    if(mines < 10) printf(" F%d    ", mines);
    else if(mines < 100) printf(" F%d   ", mines);
    else printf(" F%d  ", mines);
    for(int i = 0; i < x; i++){
        if(i < 9) printf("| %d ", i + 1);
        else printf("| %d", i + 1);
    }
    printf("|\n");
    printf("\n");
    for(int i = 0; i < y; i++){
        if(i < 9) printf("|  %d|  ", i + 1);
        else printf("| %d|  ", i + 1);
        for(int j = 0; j < x; j++){
            if(plansza[j][i][1] == 1){
                if(plansza[j][i][0] < 9 && plansza[j][i][0] >= 1) printf("| %d ", plansza[j][i][0]);
                else if(plansza[j][i][0] == 0) printf("| . ");
                else if(plansza[j][i][0] == 9) printf("|   ");
                else if(plansza[j][i][0] == -1) printf("| * ");
            }
            else if(plansza[j][i][1] == 2) printf("| F ");
            else printf("|   ");
        }
        printf("|\n");
    }
    printf("\n");
}


// Funkcja zwracającą ilość bomb otaczających dane pole
int neighbours(int x, int y, int plansza[x][y][2], int curx, int cury){
    int ile = 0;
    for(int i = curx - 1; i < curx + 2; i++){
        for(int j = cury - 1; j < cury +2; j++){
            if(i >= 0 && i < x && j >= 0 && j < y){
                if(plansza[i][j][0] == -1) ile++;
            }
        }
    }
    return ile;
}


// Funkja, która "rozlewa" planszę, dzięki czemu możliwy jest pierwszy ruch oraz szybsze odkrywanie pustych obszarów
void full(int x, int y, int plansza[x][y][2], int curx, int cury){
    if(plansza[curx][cury][0] == 0){
        for(int i = curx - 1; i < curx + 2; i++){
            for(int j = cury - 1; j < cury + 2; j++){
                if(i >= 0 && i < x && j >= 0 && j < y){
                    if(plansza[i][j][1] == 0){
                        plansza[i][j][1] = 1;
                        full(x, y, plansza, i, j);
                    }
                    plansza[i][j][1] = 1;
                }
            }
        }
    }
}


// Funkcja sprawdzająca czy gracz wygrał
int gamecheck(int x, int y, int plansza[x][y][2]){
    int licznik = 0;
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            if(plansza[i][j][1] == 0 || (plansza[i][j][0] != -1 && plansza[i][j][1] == 2)) licznik++;
        }
    }
    if(licznik > 0) return 0;
    return 1;
}
