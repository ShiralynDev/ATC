#include <iostream>
#include <ATC.h>
#include <raylib.h>
#include <RaylibAdditions.hpp>

int main() {
    std::cout << "Hello world!";

    InitWindow(1500, 400, "ATC Simulator");
    SetTargetFPS(60);

    Texture2D ATCPanel = LoadTexture("../res/textures/cleanATC.png");

    Rectangle startup = {0, ATCPanel.height, 200, 50};
    RaylibAdditions::ButtonClass startupButton = {startup, "Start ATC", 20, GRAY, WHITE, WHITE, 5, 1};

    ATCReturnData returnedData;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(ATCPanel, 0, 0, WHITE);
        RaylibAdditions::drawButton(&startupButton);

        RaylibAdditions::updateButtonstate(&startupButton);
        if (startupButton.state == 2)
            toggleATC(1);

        returnedData = runATC(ATCData());

        DrawText(std::string(1, returnedData.mainIndicator0).c_str(), 100, 100, 25, WHITE);

        DrawText(std::string("ATC status = " + std::to_string(returnedData.ATCStatus)).c_str(), 1050, 0, 10, WHITE);
        DrawText(std::string("ATC preind = " + std::string(1, returnedData.preIndicator0) + std::string(1, returnedData.preIndicator1) + std::string(1, returnedData.preIndicator2)).c_str(), 1050, 15, 10, WHITE);
        DrawText(std::string("ATC mainind = " + std::string(1, returnedData.mainIndicator0) + std::string(1, returnedData.mainIndicator1) + std::string(1, returnedData.mainIndicator2)).c_str(), 1050, 30, 10, WHITE);
    
        EndDrawing();
    }

    return 0;
}