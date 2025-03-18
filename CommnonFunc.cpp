#include "CommonFunc.h"

// Định nghĩa các biến toàn cục
SDL_Window* g_window = nullptr;
SDL_Renderer* g_screen = nullptr;
SDL_Event g_event;


// Khởi tạo SDL
bool initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    g_window = SDL_CreateWindow("Plane Battle!!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (g_window == nullptr) {
        std::cout<< "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if (g_screen == nullptr) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1) {
        std::cout << "TTF could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "SDL_mixer could not initialize! Mix_Error: " << Mix_GetError() << std::endl;
        return false;
    }

    return true;
}

// Đóng SDL và giải phóng tài nguyên
void closeSDL() {
    if (g_screen != nullptr) {
        SDL_DestroyRenderer(g_screen);
        g_screen = nullptr;
    }

    if (g_window != nullptr) {
        SDL_DestroyWindow(g_window);
        g_window = nullptr;
    }

    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}
