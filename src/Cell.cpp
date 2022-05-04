#include "Cell.h"


CELL::CELL() {
    can_edit = false;
    number = 0;
    hitbox->h = 64;
    hitbox->w = 64;
}


CELL::~CELL() {
    delete hitbox;
}

void CELL::set_number(const int num) {
    if(num != number) number = num;
}

int CELL::get_number() const {
    return number;
}

bool CELL::get_edit() const {
    return can_edit;
}

void CELL::set_edit(const bool editable) {
    if(editable != can_edit) can_edit = editable;
}

SDL_Rect *CELL::get_hitbox() {
    return hitbox;
}

void CELL::set_hitbox_offset(int x, int y) {
    hitbox->x = x;
    hitbox->y = y;
}

CURSOR::CURSOR() {
    row = 0;
    col = 0;
}

void CURSOR::move(int x, int y) {
    row += x;
    col += y;
    if(row > 8) row = 0;
    else if(row < 0) row = 8;
    if(col > 8) col = 0;
    else if(col < 0) col = 8;
}

int CURSOR::get_x() {
    return col;
}

int CURSOR::get_y() {
    return row;
}
