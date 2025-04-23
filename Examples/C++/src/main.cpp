#include <iostream>
#include <ATC.h>
#include <raylib.h>

int main() {
    std::cout << "Hello world!";

    InitWindow(1500, 400, "ATC Simulator");
    SetTargetFPS(60);

    Texture2D ATCPanel = LoadTexture("../res/textures/cleanATC.png");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexture(ATCPanel, 0, 0, WHITE);
    
        EndDrawing();
    }

    return 0;
}