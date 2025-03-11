#ifndef ENEMY_H
#define ENEMY_H

#include "CommonFunc.h"
#include "bullet.h"

class Enemy {
public:
    Enemy(SDL_Renderer* renderer, const char* imagePath, int x, int y, int w, int h);
    ~Enemy();

    void render(SDL_Renderer* renderer);
    void move();
    void shoot(SDL_Renderer* renderer, std::vector<Bullet>& enemyBullets);
    bool checkCollision(const SDL_Rect& otherRect) const;
    bool isDestroyed() const;
    void takeDamage();

private:
    SDL_Texture* texture;
    SDL_Rect rect;
    int health;
    bool destroyed;
};

#endif // ENEMY_H
