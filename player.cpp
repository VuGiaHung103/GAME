#include "player.h"


Player::Player(SDL_Renderer* renderer, const char* imagePath, int x, int y, int w, int h) {
    texture = IMG_LoadTexture(renderer, imagePath);
    rect = {x, y, w, h};
    health = 6; // Người chơi có 6 máu
    moveLeft = false;
    moveRight = false;
}


Player::~Player() {
    SDL_DestroyTexture(texture);
}

void Player::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Player::handleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_LEFT) moveLeft = true;
        if (event.key.keysym.sym == SDLK_RIGHT) moveRight = true;
    }
    if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_LEFT) moveLeft = false;
        if (event.key.keysym.sym == SDLK_RIGHT) moveRight = false;
    }
}

void Player::move() {
    if (moveLeft && rect.x > 0) rect.x -= 5;
    if (moveRight && rect.x < SCREEN_WIDTH - rect.w) rect.x += 5;
}
void Player::takeDamage() {
    health--;
    if (health < 0) health = 0;
}


SDL_Rect Player::getRect() const {
    return rect;
}

int Player::getHealth() const {
    return health;
}

