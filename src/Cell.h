#include <SDL2/SDL.h>

#ifndef CPPSUDOKU_CELL_H
#define CPPSUDOKU_CELL_H

class CURSOR {
    int row, col;
public:
    CURSOR();

    void move(int x, int y);
    int get_x();
    int get_y();
};

class CELL {
    bool can_edit;
    int number;
    SDL_Rect *hitbox = new SDL_Rect;
public:
    CELL();
    ~CELL();

    void set_number(int num);
    int get_number() const;
    bool get_edit() const;
    void set_edit(bool editable);
    SDL_Rect *get_hitbox();
    void set_hitbox_offset(int x, int y);
};


#endif
