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

    Rectangle startup = {0, float(ATCPanel.height), 200, 50};
    RaylibAdditions::ButtonClass startupButton = {startup, "Start ATC", 20, GRAY, WHITE, WHITE, 5, 1};
    Rectangle switchATCType = {0, startupButton.rect.y + startupButton.rect.height, 200, 50};
    RaylibAdditions::ButtonClass switchATCTypeButton = {switchATCType, "Use ABB ATC", 20, GRAY, WHITE, WHITE, 5, 1};
    Rectangle dataEntry = {642, 40, 20, 20};
    RaylibAdditions::ButtonClass dataEntryButton = {dataEntry, "", 20, BLANK, BLANK, BLANK, 0, 1};
    
    RaylibAdditions::SpeedometerClass speedometer = {{200, float(ATCPanel.height), 300, 300}, 0, 200, 160, 380, 21, "km/h", WHITE, YELLOW};
    Rectangle speedButtonRect = {200, 300, 50, 50};
    RaylibAdditions::ButtonClass speedRemove = {speedButtonRect, "-10", 20, GRAY, WHITE, WHITE, 5, 1};
    speedButtonRect.x += 300 - 50;
    RaylibAdditions::ButtonClass speedAdd = {speedButtonRect, "+10", 20, GRAY, WHITE, WHITE, 5, 1};

    Rectangle speedButtonRectSmall = {250, 300, 50, 50};
    RaylibAdditions::ButtonClass speedRemoveSmall = {speedButtonRectSmall, "-1", 20, GRAY, WHITE, WHITE, 5, 1};
    speedButtonRectSmall.x += 200 - 50;
    RaylibAdditions::ButtonClass speedAddSmall = {speedButtonRectSmall, "+1", 20, GRAY, WHITE, WHITE, 5, 1};

    RaylibAdditions::SpeedometerClass brakePressure = {{500, float(ATCPanel.height), 300, 300}, 0, 10, 160, 380, 11, "kPa", WHITE, RED};
    Rectangle brakePressureButtonRect = {500, 300, 50, 50};
    RaylibAdditions::ButtonClass brakePressureRemove = {brakePressureButtonRect, "-0,5", 20, GRAY, WHITE, WHITE, 5, 1};
    brakePressureButtonRect.x += 300 - 50;
    RaylibAdditions::ButtonClass brakePressureAdd = {brakePressureButtonRect, "+0,5", 20, GRAY, WHITE, WHITE, 5, 1};
    
    ATCReturnData returnedData;
    ATCData data = {};

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(ATCPanel, 0, 0, WHITE);
        RaylibAdditions::drawButton(&startupButton);
        RaylibAdditions::updateButtonstate(&startupButton);
        if (startupButton.state == 2) {
            if (returnedData.ATCStatus == 1)
                toggleATC(0);
            if (returnedData.ATCStatus == 0)
                toggleATC(1);
        }

        if (returnedData.ATCStatus == 1)
            startupButton.text = "Turn off ATC";
        if (returnedData.ATCStatus == 0)
            startupButton.text = "Turn on ATC";

        RaylibAdditions::drawButton(&switchATCTypeButton);
        RaylibAdditions::updateButtonstate(&switchATCTypeButton);
        if (switchATCTypeButton.state == 2) {
            toggleSystemType(!getSystemType());
            if (getSystemType())
                switchATCTypeButton.text = "Use SRT ATC";
            if (!getSystemType())
                switchATCTypeButton.text = "Use ABB ATC";
        }

        RaylibAdditions::updateButtonstate(&dataEntryButton, true);
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

        speedometer.drawSpeedometer();
        brakePressure.drawSpeedometer();
        brakePressure.drawNeedle({255, 4, 20, 255}, 3.0f, 0.5);

        RaylibAdditions::drawButton(&speedAdd);
        RaylibAdditions::drawButton(&speedRemove);
        RaylibAdditions::updateButtonstate(&speedAdd);
        RaylibAdditions::updateButtonstate(&speedRemove);

        RaylibAdditions::drawButton(&speedAddSmall);
        RaylibAdditions::drawButton(&speedRemoveSmall);
        RaylibAdditions::updateButtonstate(&speedAddSmall);
        RaylibAdditions::updateButtonstate(&speedRemoveSmall);

        if (speedAdd.state == 2 && speedometer.value + 10 <= 200)
            speedometer.value += 10;
        if (speedRemove.state == 2 && speedometer.value - 10 >= 0)
            speedometer.value -= 10;
        if (speedAddSmall.state == 2 && speedometer.value + 1 <= 200)
            speedometer.value += 1;
        if (speedRemoveSmall.state == 2 && speedometer.value - 1 >= 0)
            speedometer.value -= 1;

        RaylibAdditions::drawButton(&brakePressureAdd);
        RaylibAdditions::drawButton(&brakePressureRemove);
        RaylibAdditions::updateButtonstate(&brakePressureAdd);
        RaylibAdditions::updateButtonstate(&brakePressureRemove);

        if (brakePressureRemove.state == 2 && brakePressure.value - 0.5 >= 0)
            brakePressure.value -= 0.5;
        if (brakePressureAdd.state == 2 && brakePressure.value + 0.5 <= 10)
            brakePressure.value += 0.5;

        EndDrawing();
    }

    return 0;
}