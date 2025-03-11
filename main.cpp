#include "CommonFunc.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"

int main(int argc, char* argv[]) {
std::cout << "Program Started !!!";

   if (!initSDL()) {
    std::cout << "Failed to initialize SDL!" << std::endl;

    return 1;
}


    Player player(g_screen, "player.png", SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, 50, 50);
    std::vector<Bullet> bullets;
    std::vector<Bullet> enemyBullets;
    std::vector<Enemy> enemies;


    for (int i = 0; i < 5; ++i) {
        enemies.push_back(Enemy(g_screen, "enemy.png", i * 100, 50, 50, 50));
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
                    bullets.push_back(Bullet(g_screen, "bullet.png", player.getRect().x + 20, player.getRect().y, 10, 20));
                }
            }
        }

        player.move();

        // Di chuyển Bullet
        for (auto& bullet : bullets) {
            bullet.move(0, -10);
        }

        // Di chuyển Enemy và bắn đạn
        for (auto& enemy : enemies) {
            enemy.move();
            if (rand() % 100 < 2) { // Xác suất bắn đạn
                enemy.shoot(g_screen, enemyBullets); // Truyền renderer vào đây
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

    if (SDL_HasIntersection(&bulletRect, &playerRect)) { // Đã sửa lỗi
        player.takeDamage();
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
                if (player.getHealth() <= 0) {
                    gameOver = true;
                }
            }
        }

        // Xóa các Enemy đã bị tiêu diệt
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& enemy) {
            return enemy.isDestroyed();
        }), enemies.end());

        // Vẽ lại màn hình
        SDL_SetRenderDrawColor(g_screen, 0, 0, 0, 255);
        SDL_RenderClear(g_screen);

        player.render(g_screen);

        for (auto& bullet : bullets) {
            bullet.render(g_screen);
        }

        for (auto& bullet : enemyBullets) {
            bullet.render(g_screen);
        }

        for (auto& enemy : enemies) {
            enemy.render(g_screen);
        }

        SDL_RenderPresent(g_screen);
        SDL_Delay(16);
    }

    if (gameOver) {
        std::cout << "Game Over!" << std::endl;
    }

    closeSDL();
    return 0;
}

