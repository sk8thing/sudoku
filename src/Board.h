#include <random>
#include "Cell.h"

#ifndef CPPSUDOKU_BOARD_H
#define CPPSUDOKU_BOARD_H


class BOARD {
    CELL **game_board = new CELL*[9];
    CURSOR *cursor = new CURSOR;
public:
    BOARD();
    ~BOARD();

    CELL **get_cells();
    CURSOR *get_cursor();
    void generate();
    bool can_place(int col, int row, int num);
    void clear_board();
    bool fill(bool solve);
    bool is_completed();
    bool is_full();
};


#endif
