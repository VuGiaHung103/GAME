
#include "bullet.h"

Bullet::Bullet(SDL_Renderer* renderer, const char* imagePath, int x, int y, int w, int h) {
    texture = IMG_LoadTexture(renderer, imagePath);
    rect = {x, y, w, h};
}

Bullet::~Bullet() {
    SDL_DestroyTexture(texture);
}

void Bullet::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Bullet::move(int dx, int dy) {
    rect.x += dx;
    rect.y += dy;
}

SDL_Rect Bullet::getRect() const {
    return rect;
}
