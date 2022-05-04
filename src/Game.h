#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Board.h"

#ifndef CPPSUDOKU_GAME_H
#define CPPSUDOKU_GAME_H


class GAME {
    bool is_running;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *board_texture;
    SDL_Texture *number_texture[9];
    SDL_Texture *cursor_texture;
    SDL_Texture *locked_texture;
    SDL_Texture *win_texture;
    SDL_Surface *icon;
    BOARD *board = nullptr;
public:
    GAME();
    ~GAME();

    void init();
    void handle_events();
    void render();
    SDL_Texture *load_texture(const char *texture);
    bool running() const;
};


#endif
