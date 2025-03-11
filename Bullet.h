
#ifndef BULLET_H
#define BULLET_H

#include"CommonFunc.h"

class Bullet {
public:
    Bullet(SDL_Renderer* renderer, const char* imagePath, int x, int y, int w, int h);
    ~Bullet();

    void render(SDL_Renderer* renderer);
    void move(int dx, int dy);
    SDL_Rect getRect() const;

private:
    SDL_Texture* texture;
    SDL_Rect rect;
};

#endif // BULLET_H
