#include <iostream>
#include <ATC.h>
#include <raylib.h>
#include <RaylibAdditions.hpp>

int main() {
    std::cout << "Hello world!";

    InitWindow(1500, 400, "ATC Simulator");
    SetTargetFPS(60);

    InitAudioDevice();
    Sound ATC1 = LoadSound("../res/audio/ATC1.wav");
    Sound ATC2 = LoadSound("../res/audio/ATC2.wav"); // get better audio

    Texture2D ATCPanel = LoadTexture("../res/textures/cleanATC.png");
    Rectangle preInd = {61, 28, 59, 24};
    Rectangle mainInd = {234, 23, 75, 30};

    Rectangle startup = {0, ATCPanel.height, 200, 50};
    RaylibAdditions::ButtonClass startupButton = {startup, "Start ATC", 20, GRAY, WHITE, WHITE, 5, 1};
    Rectangle dataEntry = {642, 40, 20, 20};
    RaylibAdditions::ButtonClass dataEntryButton = {dataEntry, "", 20, BLANK, BLANK, BLANK, 0, 1};

    ATCReturnData returnedData;
    ATCData data = {};

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(ATCPanel, 0, 0, WHITE);
        RaylibAdditions::drawButton(&startupButton);
        RaylibAdditions::updateButtonstate(&startupButton);
        if (startupButton.state == 2)
            toggleATC(1);

        RaylibAdditions::updateButtonstate(&dataEntryButton);
        if (dataEntryButton.state == 2)
            data.dataEntryButton = true;
        else
            data.dataEntryButton = false;

        returnedData = runATC(data);

        if (returnedData.shuntingLamp) DrawCircle(25, 25, 5, RED);
        if (returnedData.ATCError) DrawCircle(150, 40, 5, RED);
        if (returnedData.BaliseError) DrawCircle(180, 40, 5, YELLOW);
        if (returnedData.speeding) DrawCircle(212, 40, 5, GREEN);
        if (returnedData.releaseLamp) DrawCircle(340, 25, 5, YELLOW);
        if (returnedData.increaseLamp) DrawCircle(392, 25, 5, GREEN);
        if (returnedData.dataEntryLamp) DrawCircle(652, 25, 5, RED);
        if (returnedData.smallError) DrawCircle(1007, 37, 5, YELLOW);

        if (returnedData.toneF1 && !IsSoundPlaying(ATC1)) PlaySound(ATC1);
        if (returnedData.toneF2 && !IsSoundPlaying(ATC2)) PlaySound(ATC2);

        int fontSizePreInd = 20;
        DrawText(std::string(1, returnedData.preIndicator0).c_str(), preInd.x + ((preInd.width/4) * 1) - fontSizePreInd / 2, preInd.y + preInd.height/2 - fontSizePreInd/2, fontSizePreInd, GREEN);
        DrawText(std::string(1, returnedData.preIndicator1).c_str(), preInd.x + ((preInd.width/4) * 2) - fontSizePreInd / 2, preInd.y + preInd.height/2 - fontSizePreInd/2, fontSizePreInd, GREEN);
        DrawText(std::string(1, returnedData.preIndicator2).c_str(), preInd.x + ((preInd.width/4) * 3) - fontSizePreInd / 2, preInd.y + preInd.height/2 - fontSizePreInd/2, fontSizePreInd, GREEN);
        int fontSizeMainInd = 20;
        DrawText(std::string(1, returnedData.mainIndicator0).c_str(), mainInd.x + ((mainInd.width/4) * 1) - fontSizeMainInd / 2, mainInd.y + mainInd.height/2 - fontSizeMainInd/2, fontSizeMainInd, GREEN);
        DrawText(std::string(1, returnedData.mainIndicator1).c_str(), mainInd.x + ((mainInd.width/4) * 2) - fontSizeMainInd / 2, mainInd.y + mainInd.height/2 - fontSizeMainInd/2, fontSizeMainInd, GREEN);
        DrawText(std::string(1, returnedData.mainIndicator2).c_str(), mainInd.x + ((mainInd.width/4) * 3) - fontSizeMainInd / 2, mainInd.y + mainInd.height/2 - fontSizeMainInd/2, fontSizeMainInd, GREEN);

        DrawText(std::string("ATC status = " + std::to_string(returnedData.ATCStatus)).c_str(), 1050, 0, 10, WHITE);
        DrawText(std::string("Tone f1 = " + std::to_string(returnedData.toneF1)).c_str(), 1050, 15, 10, WHITE);
        DrawText(std::string("Tone f2 = " + std::to_string(returnedData.toneF2)).c_str(), 1050, 30, 10, WHITE);
        DrawText(std::string("Shunting lamp = " + std::to_string(returnedData.shuntingLamp)).c_str(), 1050, 45, 10, WHITE);
        DrawText(std::string("ATC preind = " + std::string(1, returnedData.preIndicator0) + std::string(1, returnedData.preIndicator1) + std::string(1, returnedData.preIndicator2)).c_str(), 1050, 60, 10, WHITE);
        DrawText(std::string("ATC Error = " + std::to_string(returnedData.ATCError)).c_str(), 1050, 75, 10, WHITE);
        DrawText(std::string("Balise Error = " + std::to_string(returnedData.BaliseError)).c_str(), 1050, 90, 10, WHITE);
        DrawText(std::string("Speeding = " + std::to_string(returnedData.speeding)).c_str(), 1050, 105, 10, WHITE);
        DrawText(std::string("ATC mainind = " + std::string(1, returnedData.mainIndicator0) + std::string(1, returnedData.mainIndicator1) + std::string(1, returnedData.mainIndicator2)).c_str(), 1050, 120, 10, WHITE);
        DrawText(std::string("Release lamp = " + std::to_string(returnedData.releaseLamp)).c_str(), 1050, 135, 10, WHITE);
        DrawText(std::string("Increase lamp = " + std::to_string(returnedData.increaseLamp)).c_str(), 1050, 150, 10, WHITE);
        DrawText(std::string("Data entry lamp = " + std::to_string(returnedData.dataEntryLamp)).c_str(), 1050, 165, 10, WHITE);
        DrawText(std::string("Small error = " + std::to_string(returnedData.smallError)).c_str(), 1050, 180, 10, WHITE);


        EndDrawing();
    }

    return 0;
}