#include "CommonFunc.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "button.h"
#include"boss.h"

    // biến cục bộ
    int waveCount = 0;
    bool waitingNextWave = false;
    Uint32 waveStartTime = 0;
    const Uint32 WAVE_DELAY = 3000;
int main(int argc, char* argv[]) {

enum GameState {
    STATE_MENU,
    STATE_PLAYING,
    STATE_EXIT
};


   if (!initSDL()) {
    std::cout << "Failed to initialize SDL!" << std::endl;

    return 1;
}
if (!initSDL() || !InitFont()) {
    std::cout << "Failed to initialize SDL or font!" << std::endl;
    return 1;
}

 Menu menu;
   if (!menu.LoadMenu()) {
        std::cout << "Failed to load menu!" << std::endl;
        closeSDL();
        return 1;
   }

   GameState currentState = STATE_MENU;

   while (currentState != STATE_EXIT) {
       if (currentState == STATE_MENU) {
           int choice = menu.ShowMenu();
           if (choice == 1) {
               currentState = STATE_PLAYING;
           }
           else {
               currentState = STATE_EXIT;
           }
       }
       else if (currentState == STATE_PLAYING) {

SDL_Texture* g_background = nullptr;
    g_background = IMG_LoadTexture(g_screen, "D:\\gamestart_1\\game start 1\\Game_2\\picture\\background.png");
if (g_background == nullptr) {
    std::cout << "Failed to load background: " << IMG_GetError() << std::endl;
}


    Player player(g_screen, "D:\\gamestart_1\\game start 1\\Game_2\\picture\\khongphut.png", SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, 100, 70);
    std::vector<Bullet> bullets;
    std::vector<Bullet> enemyBullets;
    std::vector<Bullet> bossBullets;
    std::vector<Enemy> enemies;
    std::vector<Boss> bosses;
    Enemy::spawnWave(enemies, g_screen);
    waveCount = 1;
    waitingNextWave = false;


    bool running = true;
    bool gameOver = false;

    while (running && !gameOver) {
        while (SDL_PollEvent(&g_event)) {
            if (g_event.type == SDL_QUIT) {
                running = false;
                return 0;
            }
            player.handleEvent(g_event);
            if (g_event.type == SDL_KEYDOWN) {
                    if (g_event.type == SDL_KEYDOWN) {

    if (g_event.key.keysym.sym == SDLK_p) {
        running = false;
        currentState = STATE_MENU;
    }
}

    if (g_event.key.keysym.sym == SDLK_SPACE) {
    int bulletX = player.getRect().x + player.getRect().w / 2 - 10;
    int bulletY = player.getRect().y - 20;
    if (player.isUsingSpecialBullet()) {
        bullets.push_back(Bullet(g_screen, "D:\\gamestart_1\\game start 1\\Game_2\\picture\\triple_bullet.png", bulletX, bulletY, 30, 50, 3));
    } else {
        bullets.push_back(Bullet(g_screen, "D:\\gamestart_1\\game start 1\\Game_2\\picture\\onebullet.png", bulletX, bulletY, 10, 20, 1));
    }
}

    if (g_event.key.keysym.sym == SDLK_1) {
    player.activateSpecialBullet();
}
}
        }
        player.move();
        player.updateSpecialState();
        // Di chuyển Bullet
        for (auto& bullet : bullets) {

            bullet.render(g_screen);
            bullet.move(0, -7);
        }
  for (auto& boss : bosses) {
    boss.move(player.getRect());
    boss.render(g_screen);
    if (rand() % 100 < 2) {
        boss.shootSpecial(g_screen, enemyBullets);
    }
}


        // Di chuyển Enemy và bắn đạn
        for (auto& enemy : enemies) {

           enemy.move(player.getRect());
            if (rand() % 100 < 1) { // Xác suất bắn đạn
                enemy.shoot(g_screen, enemyBullets);
            }
        }

        // Di chuyển đạn của kẻ địch
        for (auto& bullet : enemyBullets) {
            bullet.move(0, 3);
        }

        // Kiểm tra va chạm giữa đạn của người chơi và Enemy || người chơi và boss
        for (auto& bullet : bullets) {
            for (auto& enemy : enemies) {
                if (enemy.checkCollision(bullet.getRect())) {
                    enemy.takeDamage(bullet.getDamage());
                    player.addEnergy(5);
                    bullet = bullets.back(); // Xóa đạn bằng cách gán nó vào phần tử cuối
                    bullets.pop_back();     // Xóa phần tử cuối
                    break;
                }
            }
            }
for (auto& boss : bosses) {
    boss.move(player.getRect());
    boss.render(g_screen);
    if (rand() % 100 < 2) {
        boss.shootSpecial(g_screen, enemyBullets);
    }
}


        // Kiểm tra va chạm giữa đạn của kẻ địch và người chơi
       for (auto& bullet : enemyBullets) {
    SDL_Rect bulletRect = bullet.getRect();
    SDL_Rect playerRect = player.getRect();

    if (SDL_HasIntersection(&bulletRect, &playerRect)) {
        player.takeDamage();

        bullet = enemyBullets.back();
        enemyBullets.pop_back();
        if (player.getHealth() <= 0) {
            gameOver = true;
        }
    }
}for (auto& bullet : bullets) {
    SDL_Rect bulletRect = bullet.getRect();

    for (auto& boss : bosses) {
        SDL_Rect bossRect = boss.getRect();

        if (SDL_HasIntersection(&bulletRect, &bossRect)) {
            boss.takeDamage(bullet.getDamage());
            player.addEnergy(10);
            bullet = bullets.back();  // Gán viên đạn cuối
            bullets.pop_back();       // Xóa viên đạn đã bắn
            break;                    // Thoát vòng for boss để tránh trùng va chạm
        }
    }
}


      for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
   SDL_Rect playerHitboxV = player.getHitboxVertical();
SDL_Rect playerHitboxH = player.getHitboxHorizontal();

SDL_Rect enemyHitboxV = enemyIt->getHitboxVertical();
SDL_Rect enemyHitboxH = enemyIt->getHitboxHorizontal();

if (SDL_HasIntersection(&playerHitboxV, &enemyHitboxV) ||
    SDL_HasIntersection(&playerHitboxV, &enemyHitboxH) ||
    SDL_HasIntersection(&playerHitboxH, &enemyHitboxV) ||
    SDL_HasIntersection(&playerHitboxH, &enemyHitboxH)) {
        player.takeDamage();

        // Xóa enemy ngay lập tức sau khi va chạm
        enemyIt = enemies.erase(enemyIt);

        // Kiểm tra nếu Player hết máu, thoát vòng lặp ngay
        if (player.getHealth() <= 0) {
            gameOver = true;
            std::cout << "Game Over!" << std::endl;
            break;
        }
    } else {
        ++enemyIt;  // Nếu không có va chạm, tiếp tục duyệt
    }
}

for (auto it = bosses.begin(); it != bosses.end();) {
    if (it->isDestroyed()) {
        it = bosses.erase(it);  // Xóa boss khỏi danh sách và cập nhật iterator
    } else {
        ++it;  // Tiếp tục nếu boss chưa bị tiêu diệt
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
            // Nếu không còn enemy và boss -> bắt đầu đếm thời gian chuẩn bị wave mới
        if (!waitingNextWave && enemies.empty() && bosses.empty()) {
    waitingNextWave = true;
    waveStartTime = SDL_GetTicks();
}

if (waitingNextWave && SDL_GetTicks() - waveStartTime >= WAVE_DELAY) {
    waveCount++;  // Lần đầu tiên là wave 1
    waitingNextWave = false;
    //spawn boss
    if (waveCount == 3 || waveCount == 6 || waveCount == 8) {
        std::string bossImg;
        if (waveCount == 3) bossImg = "D:\\gamestart_1\\game start 1\\Game_2\\picture\\boss_1.png";
        if (waveCount == 6) bossImg = "D:\\gamestart_1\\game start 1\\Game_2\\picture\\boss_2.png";
        if (waveCount == 8) bossImg = "D:\\gamestart_1\\game start 1\\Game_2\\picture\\boss_3.png";

        Boss newBoss(g_screen, bossImg, SCREEN_WIDTH / 2 - 100, 60, 200, 150);
        bosses.push_back(newBoss);
    }
     else {
        Enemy::spawnWave(enemies, g_screen);
    }
}



        // Vẽ lại màn hình
        SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
        SDL_RenderClear(g_screen);
        SDL_RenderCopy(g_screen, g_background, NULL, NULL);
        player.render(g_screen);
        std::string waveText = "Wave: " + std::to_string(waveCount);
        SDL_Color color = { 0, 0, 0 };
        SDL_Surface* textSurface = TTF_RenderText_Solid(g_font, waveText.c_str(), color);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(g_screen, textSurface);
        SDL_Rect textRect = { 1050, 20, textSurface->w, textSurface->h };

        SDL_RenderCopy(g_screen, textTexture, NULL, &textRect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);


        for (auto& boss : bosses) {
            boss.render(g_screen);
        }
        for (auto& bullet : bullets) {
            bullet.render(g_screen);
        }
        for (auto& enemy : enemies) {
            enemy.render(g_screen);
        }
        for (auto& bullet : enemyBullets) {
            bullet.render(g_screen);
        }
        for (auto& boss : bosses) {
            boss.render(g_screen);
        }
        SDL_Rect bg = { 20, 20, 240, 20 };
SDL_Rect bar = { 20, 20, player.getEnergy() * 4, 20 };

SDL_SetRenderDrawColor(g_screen, 100, 100, 100, 255); // khung nền
SDL_RenderFillRect(g_screen, &bg);

if (player.isUsingSpecialBullet())
    SDL_SetRenderDrawColor(g_screen, 255, 100, 0, 255); // cam
else
    SDL_SetRenderDrawColor(g_screen, 0, 255, 0, 255);   // xanh

SDL_RenderFillRect(g_screen, &bar);

        SDL_RenderPresent(g_screen);
        SDL_Delay(16);
    }

     if (g_background != nullptr) {
        SDL_DestroyTexture(g_background);
        g_background = nullptr;
    }
       }
 }
    menu.Free();

    CloseFont();
    closeSDL();

    return 0;
}
