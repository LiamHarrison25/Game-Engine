#include <iostream>
#include "GameManager.h"

#define SCREEN_WIDTH (1920)
#define SCREEN_HEIGHT (1080)

const int TARGET_FPS = 60;

#define WINDOW_TITLE "Game-Engine"

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(TARGET_FPS);

    GameManager::CreateInstance();
    GameManager* gameManager = GameManager::GetInstance();    

    gameManager->DoLoop();

    gameManager->DestroyInstance();
    gameManager = nullptr;

    CloseWindow();

    return 0;
}
