#include "enemy.h"

Enemy::Enemy(SDL_Renderer* renderer, const char* imagePath, int x, int y, int w, int h) {
    texture = IMG_LoadTexture(renderer, imagePath);
    if (!texture) {
        std::cout << "Failed to load enemy texture: " << IMG_GetError() << std::endl;
    }
    rect = {x, y, w, h};
    health = 2; // Enemy cần 2 viên đạn để bị tiêu diệt
    destroyed = false;
}


void Enemy::render(SDL_Renderer* renderer) {

    if (!destroyed) {
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }
}

void Enemy::move() {
    if (!destroyed) {
        rect.x += 2; // Di chuyển sang phải
        if (rect.x > SCREEN_WIDTH - rect.w) {
            rect.x = 0; // Quay lại bên trái
            rect.y += 50; // Di chuyển xuống dưới
        }
    }
}


void Enemy::shoot(SDL_Renderer* renderer, std::vector<Bullet>& enemyBullets) {
    if (!destroyed) {
        enemyBullets.push_back(Bullet(renderer, "D:\\gamestart_1\\game start 1\\Game_2\\picture\\enemybullet.png", rect.x + rect.w / 2, rect.y + rect.h, 5, 10));
    }
}

bool Enemy::checkCollision(const SDL_Rect& otherRect) const {
    if (destroyed) return false;
    return SDL_HasIntersection(&rect, &otherRect);
}

bool Enemy::isDestroyed() const {
    return destroyed;
}

void Enemy::takeDamage() {
    health--;
    if (health <= 0) {
        destroyed = true;
    }
}
