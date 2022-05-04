#include "Board.h"

BOARD::BOARD() {
    int crow = 0, ccol = 0;
    for(int i = 0; i < 9; i++) game_board[i] = new CELL[9];
    for(int i = 0; i < 9; i++){
        if(i == 0) ccol += 4; // Thick border 3px;
        else if(i % 3 == 0) ccol += 4;
        else ccol += 2; // Thin border 1px;
        crow = 0;
        for(int j = 0; j < 9; j++){
            if(j == 0) crow += 4;
            else if(j % 3 == 0) crow += 4;
            else crow += 2;
            game_board[i][j].set_hitbox_offset(64 * j + crow, 64 * i + ccol);
        }
    }
    generate();
}

BOARD::~BOARD() {
    delete[] game_board;
    delete cursor;
}

CELL **BOARD::get_cells() {
    return game_board;
}

CURSOR *BOARD::get_cursor() {
    return cursor;
}

void BOARD::generate() {
    int number, row, col, remove;
    std::random_device rand;
    std::mt19937 rng(rand());
    std::uniform_int_distribution<> num(1, 9);
    std::uniform_int_distribution<> rem(54, 73);
    remove = rem(rng);
    clear_board();
    //Diagonal
    for(int k = 0; k < 9; k += 3){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                do{
                    number = num(rng);
                }while(!can_place(i + k, j + k, number));
                game_board[i + k][j + k].set_number(number);
            }
        }
    }
    fill(false);
    while(remove){
        row = num(rng) - 1;
        col = num(rng) - 1;
        game_board[col][row].set_number(0);
        game_board[col][row].set_edit(true);
        remove--;
    }
}

bool BOARD::can_place(int col, int row, int num) {
    //Box
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(game_board[(col - col % 3) + i][(row - row % 3) + j].get_number() == num) return false;
        }
    }
    //Col
    for(int j = 0; j < 9; j++){
        if(game_board[j][row].get_number() == num) return false;
    }
    //Row
    for(int k = 0; k < 9; k++){
        if(game_board[col][k].get_number() == num) return false;
    }
    return true;
}

void BOARD::clear_board() {
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            game_board[j][i].set_number(0);
            game_board[j][i].set_edit(false);
        }
    }
}

bool BOARD::fill(bool solve) {
    if(solve){
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                if(game_board[j][i].get_edit()) game_board[j][i].set_number(0);
            }
        }
    }
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(game_board[j][i].get_number() == 0){
                for(int k = 1; k <= 9; k++){
                    if(can_place(j, i, k)){
                        game_board[j][i].set_number(k);
                        if(fill(false)) return true;
                        game_board[j][i].set_number(0);
                    }
                }
                return false;
            }
        }
    }
    return true;
}

bool BOARD::is_completed() {
    int sum;
    if(!is_full()) return false;
    //Col && Row
    for(int i = 0; i < 9; i++){
        sum = 0;
        for(int j = 0; j < 9; j++){
            sum += game_board[j][i].get_number();
        }
        if(sum != 45) return false;
    }
    //Box ?
    for(int col = 0; col < 9; col += 3){
        for(int row = 0; row < 9; row += 3){
            sum = 0;
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    sum += game_board[col + j][row + i].get_number();
                }
            }
            if(sum != 45) return false;
        }
    }
    return true;
}

bool BOARD::is_full() {
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(game_board[j][i].get_number() == 0) return false;
        }
    }
    return true;
}
