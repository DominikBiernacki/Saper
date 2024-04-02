#include "header.h"


// Wypisuje logo gry "Saper"
void logo(){
    printf(" _____   ___  ______  _____ ______ \n"
           "/  ___| / _ \\ | ___ \\|  ___|| ___ \\\n"
           "\\ `--. / /_\\ \\| |_/ /| |__  | |_/ /\n"
           " `--. \\|  _  ||  __/ |  __| |    / \n"
           "/\\__/ /| | | || |    | |___ | |\\ \\ \n"
           "\\____/ \\_| |_/\\_|    \\____/ \\_| \\_|\n\n");
}


// Na podstawie wyboru gracza ustawia odpowiednią trudność gry
int set_difficulty(){
    char command[10];
    printf("Wybierz tryb, wpisujac odpowiednia litere:\n"
           "E - tryb latwy (8x8, 10 bomb)\nM - tryb sredni (16x16, 40 bomb)\n"
           "H - tryb trudny (24x24, 99 bomb)\nC - wlasne ustawienia planszy oraz bomb\n"
           "T - tutorial\n");
    printf("->");
    while(1){
        scanf("%s", command);
        if(strcmp(command, "E") == 0){
            clear();
            return 1;
        }
        else if(strcmp(command, "M") == 0){
            clear();
            return 2;
        }
        else if(strcmp(command, "H") == 0){
            clear();
            return 3;
        }
        else if(strcmp(command, "C") == 0){
            clear();
            return 4;
        }
        else if(strcmp(command, "T") == 0){
            printf("Gra polega na zlokalizowaniu min ukrytych na planszy. Cyfry informuja o tym, ile bomb "
                   "sasiaduje z danym polem.\nStawiaj flagi w miejsach, w ktorych sie ich spodziewasz, a takze odrywaj "
                   "pola, ktore wydaja sie bezpieczne.\nBadz jednak ostrozny, jeden zly ruch i wybuchasz!\n");
            printf("\nWybierz tryb, wpisujac odpowiednia litere:\n"
                   "E - tryb latwy (8x8, 10 bomb)\nM - tryb sredni (16x16, 40 bomb)\n"
                   "H - tryb trudny (24x24, 99 bomb)\nC - wlasne ustawienia planszy oraz bomb\n"
                   "T - tutorial\n");
            printf("->");
        }
        else{
            printf("Wpisano zla litere, sprobuj ponownie!\n");
            clear();
        }
    }
}


// Na podstawie wybranego poziomu trudności ustawia odpowiednio wymiary planszy oraz ilość bomb
void set_values(int *x, int *y, int *mines, int difficulty){
    if(difficulty == 1) *x = 8, *y = 8, *mines = 10;
    else if(difficulty == 2) *x = 16, *y = 16, *mines = 40;
    else if(difficulty == 3) *x = 24, *y = 24, *mines = 99;
    else{
        while(*x < 5 || *x > 25){
            printf("Wybierz pierwszy wymiar (5-25): \n");
            scanf("%d", x);
            if(*x < 5 || *x > 25) printf("Zly wymiar, sprobuj ponownie!\n");
        }
        clear();
        while(*y < 5 || *y > 25){
            printf("Wybierz drugi wymiar (5-25): \n");
            scanf("%d", y);
            if(*y < 5 || *y > 25) printf("Zly wymiar, sprobuj ponownie!\n");
        }
        clear();
        while(*mines < (*x * *y)/10 || *mines > (*x * *y)/3){
            printf("Wybierz ilosc bomb (%d-%d): \n", (*x * *y)/10, (*x * *y)/3);
            scanf("%d", mines);
            if(*mines < (*x * *y)/10 || *mines > (*x * *y)/3) printf("Zla ilosc bomb, sprobuj ponownie!\n");
        }
    }
}


// Inicjuje początkowy stan planszy po pierwszym ruchu gracza
void board_init(int x, int y, int plansza[x][y][2], int mines){
    int ruchX, ruchY, randX, randY, minescopy = mines;
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            plansza[i][j][0] = 9;
            plansza[i][j][1] = 0;
        }
    }
    print(x, y, plansza, mines);
    while(1){
        printf("Podaj pierwszy ruch <kolumna> <wiersz>:\n");
        while(scanf("%d%d", &ruchX, &ruchY) != 2){
            printf("Niepoprawny ruch, sprobuj ponownie!\n");
            clear();
        }
        ruchX--;
        ruchY--;
        if(ruchX >= 0 && ruchX < x && ruchY >= 0 && ruchY < y) break;
        printf("Niepoprawny ruch, sprobuj ponownie!\n");

    }
    for(int i = ruchX - 1; i < ruchX + 2; i++){
        for(int j = ruchY - 1; j < ruchY +2; j++){
            if(i >= 0 && i < x && j >= 0 && j < y){
                plansza[i][j][0] = 0;
                if(i == ruchX && j == ruchY) plansza[i][j][1] = 1;
            }
        }
    }
    srand(time(NULL));
    while(minescopy > 0){
        randX = rand() % x;
        randY = rand() % y;
        if(plansza[randX][randY][0] == 9){
            plansza[randX][randY][0] = -1;
            minescopy--;
        }
    }
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            if(plansza[i][j][0] != -1) plansza[i][j][0] = neighbours(x, y, plansza, i, j);
        }
    }
    full(x, y, plansza, ruchX, ruchY);
    print(x, y, plansza, mines);
}


// Główny loop gry, funkcja prosi o kolejne ruchy gracza do momentu zakończenia gry wygraną bądź przegraną
void main_game(int x, int y, int plansza[x][y][2], int mines, int *game_over){
    int ruchX, ruchY;
    char tryb;
    while(*game_over == 0){
        printf("Podaj ruch <tryb (c/f)> <kolumna> <wiersz>:\n");
        clear();
        while(scanf("%c%d%d", &tryb, &ruchX, &ruchY) != 3){
            printf("Niepoprawny ruch, sprobuj ponownie!\n");
            clear();
        }
        ruchX--;
        ruchY--;
        if(ruchX >= 0 && ruchX < x && ruchY >= 0 && ruchY < y && plansza[ruchX][ruchY][1] != 1){
            if(tryb == 'c' && plansza[ruchX][ruchY][1] == 0){
                plansza[ruchX][ruchY][1] = 1;
                if(plansza[ruchX][ruchY][0] == -1){
                    *game_over = -1;
                }
                else if(plansza[ruchX][ruchY][0] == 0) full(x, y, plansza, ruchX, ruchY);
                print(x, y, plansza, mines);
            }
            else if(tryb == 'f'){
                if(plansza[ruchX][ruchY][1] == 2) plansza[ruchX][ruchY][1] = 0, mines++, print(x, y, plansza, mines);
                else if(mines > 0) plansza[ruchX][ruchY][1] = 2, mines--, print(x, y, plansza, mines);
                else printf("Wykorzystano wszystkie flagi, sprobuj ponownie!\n");
            }
            else printf("Niepoprawny ruch, sprobuj ponownie!\n");
        }
        else printf("Niepoprawny ruch, sprobuj ponownie!\n");
        if(*game_over == 0) *game_over = gamecheck(x, y, plansza);
    }
}


// Na podstawie wyniku gry wypisuje "YOU WON" lub "YOU LOST"
void endscreen(int game_over){
    if(game_over == -1) printf("__   _______ _   _   _     _____ _____ _____ \n"
                               "\\ \\ / /  _  | | | | | |   |  _  /  ___|_   _|\n"
                               " \\ V /| | | | | | | | |   | | | \\ `--.  | |  \n"
                               "  \\ / | | | | | | | | |   | | | |`--. \\ | |  \n"
                               "  | | \\ \\_/ / |_| | | |___\\ \\_/ /\\__/ / | |  \n"
                               "  \\_/  \\___/ \\___/  \\_____/\\___/\\____/  \\_/  \n");
    else printf("__   _______ _   _   _    _  _____ _   _ \n"
                "\\ \\ / /  _  | | | | | |  | ||  _  | \\ | |\n"
                " \\ V /| | | | | | | | |  | || | | |  \\| |\n"
                "  \\ / | | | | | | | | |/\\| || | | | . ` |\n"
                "  | | \\ \\_/ / |_| | \\  /\\  /\\ \\_/ / |\\  |\n"
                "  \\_/  \\___/ \\___/   \\/  \\/  \\___/\\_| \\_/\n");
}
