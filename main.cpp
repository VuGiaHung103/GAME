#include "CommonFunc.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"

int main(int argc, char* argv[]) {


   if (!initSDL()) {
    std::cout << "Failed to initialize SDL!" << std::endl;

    return 1;
}
SDL_Texture* g_background = nullptr;
    g_background = IMG_LoadTexture(g_screen, "D:\\gamestart_1\\game start 1\\Game_2\\picture\\background.png");
if (g_background == nullptr) {
    std::cout << "Failed to load background: " << IMG_GetError() << std::endl;
}


    Player player(g_screen, "D:\\gamestart_1\\game start 1\\Game_2\\picture\\khongphut.png", SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, 150, 150);
    std::vector<Bullet> bullets;
    std::vector<Bullet> enemyBullets;
    std::vector<Enemy> enemies;


    for (int i = 0; i < 5; ++i) {
        enemies.push_back(Enemy(g_screen, "D:\\gamestart_1\\game start 1\\Game_2\\picture\\enemy.png", i * 100, 50, 70, 70));
    }

    bool running = true;
    bool gameOver = false;

    while (running && !gameOver) {
        while (SDL_PollEvent(&g_event)) {
            if (g_event.type == SDL_QUIT) {
                running = false;
            }
            player.handleEvent(g_event);
            if (g_event.type == SDL_KEYDOWN) {
    if (g_event.key.keysym.sym == SDLK_SPACE) {
        int bulletX = player.getRect().x + player.getRect().w / 2 - 5;
        int bulletY = player.getRect().y - 10;
        bullets.push_back(Bullet(g_screen,"D:\\gamestart_1\\game start 1\\Game_2\\picture\\onebullet.png",bulletX, bulletY, 10, 20));
    }
}

        }

        player.move();

        // Di chuyển Bullet
        for (auto& bullet : bullets) {

            bullet.render(g_screen);
            bullet.move(0, -10);
        }

        // Di chuyển Enemy và bắn đạn
        for (auto& enemy : enemies) {
            enemy.move();
            if (rand() % 100 < 2) { // Xác suất bắn đạn
                enemy.shoot(g_screen, enemyBullets);
            }
        }

        // Di chuyển đạn của kẻ địch
        for (auto& bullet : enemyBullets) {
            bullet.move(0, 5);
        }

        // Kiểm tra va chạm giữa đạn của người chơi và Enemy
        for (auto& bullet : bullets) {
            for (auto& enemy : enemies) {
                if (enemy.checkCollision(bullet.getRect())) {
                    enemy.takeDamage();
                    bullet = bullets.back(); // Xóa đạn bằng cách gán nó vào phần tử cuối
                    bullets.pop_back();     // Xóa phần tử cuối
                    break;
                }
            }
        }

        // Kiểm tra va chạm giữa đạn của kẻ địch và người chơi
       for (auto& bullet : enemyBullets) {
    SDL_Rect bulletRect = bullet.getRect();
    SDL_Rect playerRect = player.getRect();

    if (SDL_HasIntersection(&bulletRect, &playerRect)) {
        player.takeDamage();
        std::cout << "va cham dan\n" ;
        bullet = enemyBullets.back();
        enemyBullets.pop_back();
        if (player.getHealth() <= 0) {
            gameOver = true;
        }
    }
}

        // Kiểm tra va chạm giữa người chơi và Enemy
        for (auto& enemy : enemies) {
            if (enemy.checkCollision(player.getRect())) {
                player.takeDamage();
                std::cout << "va cham enemy \n " ;
                if (player.getHealth() <= 0) {
                    gameOver = true;
                }
            }
        }

        // Xóa các Enemy đã bị tiêu diệt
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& enemy) {
            return enemy.isDestroyed();
        }), enemies.end());
        // Xóa đạn của người chơi nếu ra khỏi màn hình
        bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b) {
            return b.isOutOfScreen(SCREEN_HEIGHT);
            }), bullets.end());

        // Xóa đạn của kẻ địch nếu ra khỏi màn hình
        enemyBullets.erase(std::remove_if(enemyBullets.begin(), enemyBullets.end(), [](const Bullet& b) {
            return b.isOutOfScreen(SCREEN_HEIGHT);
            }), enemyBullets.end());
        // Vẽ lại màn hình
        SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
        SDL_RenderClear(g_screen);
        SDL_RenderCopy(g_screen, g_background, NULL, NULL);
        player.render(g_screen);
        for (auto& bullet : bullets) {
            bullet.render(g_screen);
        }

        for (auto& bullet : enemyBullets) {
            bullet.render(g_screen);
        }

    for (auto& enemy : enemies) {
    if (enemy.checkCollision(player.getRect())) {
        player.takeDamage();
        if (player.getHealth() <= 0) {
            gameOver = true;
        }
    }
}

        SDL_RenderPresent(g_screen);
        SDL_Delay(16);
    }

    if (gameOver) {
        std::cout << "Game Over!" << std::endl;
    }
     if (g_background != nullptr) {
        SDL_DestroyTexture(g_background);
        g_background = nullptr;
    }

    closeSDL();
    return 0;
}
