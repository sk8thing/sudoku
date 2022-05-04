#include "Game.h"

GAME *main_game = nullptr;

int main(int argc, char* argv[]){
    const int FPS = 30;
    const int FRAME_DELAY = 1000 / FPS;
    Uint32 frame_start;
    int frame_time;

    main_game = new GAME();

    while(main_game->running()){
        frame_start = SDL_GetTicks();

        main_game->handle_events();
        main_game->render();

        frame_time = SDL_GetTicks() - frame_start;
        if(FRAME_DELAY > frame_time) SDL_Delay(FRAME_DELAY - frame_time);
    }
    return 0;
}