#include "player.h"


Player::Player(SDL_Renderer* renderer, const char* imagePath, int x, int y, int w, int h) {
    texture = IMG_LoadTexture(renderer, imagePath);
    rect = {x, y, w, h};
    health = 100; // Người chơi có 6 máu
    moveLeft = false;
    moveRight = false;
    moveUp = false;
    moveDown = false;
     // Giữ nhân vật trong màn hình
    if (rect.x < 0) rect.x = 0;
    if (rect.x > SCREEN_WIDTH - rect.w) rect.x = SCREEN_WIDTH - rect.w;
    if (rect.y < 0) rect.y = 0;
    if (rect.y > SCREEN_HEIGHT - rect.h) rect.y = SCREEN_HEIGHT - rect.h;


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
        if (event.key.keysym.sym == SDLK_UP) moveUp = true;
        if (event.key.keysym.sym == SDLK_DOWN) moveDown = true;
    }
    if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_LEFT) moveLeft = false;
        if (event.key.keysym.sym == SDLK_RIGHT) moveRight = false;
        if (event.key.keysym.sym == SDLK_UP) moveUp = false;
        if (event.key.keysym.sym == SDLK_DOWN) moveDown = false;
    }
}

void Player::move() {
    if (moveLeft && rect.x > 0) rect.x -= 10;
    if (moveRight && rect.x < SCREEN_WIDTH - rect.w) rect.x += 10;
    if (moveUp && rect.y > 0) rect.y -= 10;
    if (moveDown && rect.y < SCREEN_HEIGHT - rect.h) rect.y += 10;
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

