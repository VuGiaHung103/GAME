
#ifndef PLAYER_H
#define PLAYER_H
#include"CommonFunc.h"

class Player {
public:
    Player(SDL_Renderer* renderer, const char* imagePath, int x, int y, int w, int h);
    ~Player();

    void render(SDL_Renderer* renderer);
    void handleEvent(SDL_Event& event);
    void takeDamage();

    void move();
    SDL_Rect getRect() const;
    int getHealth() const;

private:
    SDL_Texture* texture;
    SDL_Rect rect;
    int health;
    bool moveLeft, moveRight;
};
#endif // PLAYER_H
