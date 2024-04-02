#include "header.h"


int main() {
    logo();
    int difficulty = set_difficulty();

    int x = 0, y = 0, mines = 0;
    set_values(&x, &y, &mines, difficulty);

    int plansza[x][y][2];
    board_init(x, y, plansza, mines);

    int game_over = 0;
    main_game(x, y, plansza, mines, &game_over);
    endscreen(game_over);
}
