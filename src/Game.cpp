#include "Game.h"

#define ENOINPUT 66
#define ECONFIG 78

GAME::GAME() {
    init();
}

GAME::~GAME() {
    delete board;
}

void GAME::init() {
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        window = SDL_CreateWindow("Sudoku", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, 0);
        icon = IMG_Load("../assets/icon.png");
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_SetWindowIcon(window, icon);
        is_running = true;
    } else exit(ECONFIG);
    board = new BOARD();
    try {
        board_texture = load_texture("../assets/board.png");
        char *format = new char[15];
        for(int i = 0; i < 9; i++){
            sprintf(format, "../assets/%d.png", i + 1);
            number_texture[i] = load_texture(format);
        }
        delete[] format;
        cursor_texture = load_texture("../assets/cursor.png");
        locked_texture = load_texture("../assets/locked.png");
        win_texture = load_texture("../assets/win_message.png");
    } catch (int e){
        SDL_Log("[ERRNO: %d]Can't load texture", e);
        exit(e);
    }
}

void GAME::handle_events() {
    SDL_Event e;
    SDL_PollEvent(&e);
    switch(e.type){
        case SDL_QUIT:
            is_running = false;
            break;
        case SDL_KEYDOWN:
            if(!board->is_completed()){
                switch(e.key.keysym.sym){
                    case SDLK_UP:
                        board->get_cursor()->move(0, -1);
                        break;
                    case SDLK_DOWN:
                        board->get_cursor()->move(0, 1);
                        break;
                    case SDLK_RIGHT:
                        board->get_cursor()->move(1, 0);
                        break;
                    case SDLK_LEFT:
                        board->get_cursor()->move(-1, 0);
                        break;
                    case SDLK_RALT:
                        board->fill(true);
                        break;
                    case SDLK_RCTRL:
                        board->get_cells()[board->get_cursor()->get_x()][board->get_cursor()->get_y()].set_number(0);
                        break;
                    default:
                        break;
                }
                if(atoi(SDL_GetKeyName(e.key.keysym.sym)) > 0 ){
                    if(board->get_cells()[board->get_cursor()->get_x()][board->get_cursor()->get_y()].get_edit()){
                        board->get_cells()[board->get_cursor()->get_x()][board->get_cursor()->get_y()].set_number(atoi(SDL_GetKeyName(e.key.keysym.sym)));
                    }
                }
            }
            if(e.key.keysym.sym == SDLK_RSHIFT){
                board->generate();
            }
            break;
        default:
            break;
    }
}

void GAME::render() {
    CELL **sudoku_board = board->get_cells();
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, board_texture, NULL, NULL);
    SDL_RenderCopy(renderer, cursor_texture, NULL, sudoku_board[board->get_cursor()->get_x()][board->get_cursor()->get_y()].get_hitbox());
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(sudoku_board[i][j].get_number() != 0){
                SDL_RenderCopy(renderer, number_texture[sudoku_board[i][j].get_number() - 1], NULL, sudoku_board[i][j].get_hitbox());
            }
            if(!sudoku_board[i][j].get_edit()){
                SDL_RenderCopy(renderer, locked_texture, NULL, sudoku_board[i][j].get_hitbox());
            }
        }
    }
    if(board->is_completed()) SDL_RenderCopy(renderer, win_texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

bool GAME::running() const {
    return is_running;
}

SDL_Texture *GAME::load_texture(const char *texture) {
    SDL_Surface *temp = IMG_Load(texture);
    if(!temp) throw ENOINPUT;
    SDL_Texture *result = SDL_CreateTextureFromSurface(renderer, temp);
    SDL_FreeSurface(temp);
    return result;
}
