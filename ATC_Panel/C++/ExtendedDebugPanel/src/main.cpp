#include <RaylibAdditions.hpp>
#include <ShiraNet.hpp>
#include <iostream>
#include <raylib.h>
#include <string.h>

#include "networking.hpp"

ATCReturnData ATCData;

void getDataThread(ShiraNet::Sockets::TcpSocket &socket) {
    while (true) { // [taskig] use interval
        auto newData = ATCNetworking::getATCData(socket);
        if (newData.has_value()) {
            ATCData = newData.value();
        }
    }
}

int main() {
    const std::string resPath = "../../../res"; // should be ./ when built for "release" or packaged, also adjust for windows, also use filesystem path for ease of use

    RaylibAdditions::WindowClass window{"ATC_Panel_Extended_Debug", 1200, 500}; // read screen size from config later

    SetTargetFPS(60);
    SetWindowMonitor(0);
    SetExitKey(KEY_NULL);

    InitAudioDevice();
    Sound ATC1 = LoadSound((resPath + "/f1.wav").c_str()); // Better f1 tone // 1. f1 med 2,5 kHz ± 20 %. f1 aktiveras endast vid ATC-larm (verkligt eller simulerat) och är helt oberoende av om ATC-systemets matningsdon fungerar eller inte. Ljudstyrkan hos f1 kan inte regleras.
    Sound ATC2 = LoadSound((resPath + "/f2.wav").c_str()); // f2 med 400 Hz ± 10 % fyrkantvåg. f2 är styrbar från datorerna under normal drift. Den aktiveras dessutom vid ATC-larm och är härvid oberoende av om ATC-systemets matningsdon fungerar eller inte. Ljudstyrkan är reglerbar med en potentiometer på panelen.
    Texture2D ATCPanelTexture = LoadTexture((resPath + "/cleanATC.png").c_str());

    Rectangle preInd = {61, 28, 59, 24};
    Rectangle mainInd = {234, 23, 75, 30};
    Rectangle startup = {0, float(ATCPanelTexture.height), 200, 50};
    RaylibAdditions::ButtonClass startupButton = {startup, "Start ATC", 20, GRAY, WHITE, WHITE, 5, 1};

    Rectangle shunting = {17, 38, 18, 18};
    RaylibAdditions::ButtonClass shuntingButton = {shunting, "", 0, BLANK, BLANK, BLANK, 0, 1};
    Rectangle release = {333, 39, 18, 18};
    RaylibAdditions::ButtonClass releaseButton = {release, "", 0, BLANK, BLANK, BLANK, 0, 1};
    Rectangle increase = {384, 39, 18, 18};
    RaylibAdditions::ButtonClass increaseButton = {increase, "", 0, BLANK, BLANK, BLANK, 0, 1};
    Rectangle stopPassage = {484, 39, 18, 18};
    RaylibAdditions::ButtonClass stopPassageButton = {stopPassage, "", 0, BLANK, BLANK, BLANK, 0, 1};
    Rectangle dataEntry = {642, 40, 20, 20};
    RaylibAdditions::ButtonClass dataEntryButton = {dataEntry, "", 0, BLANK, BLANK, BLANK, 0, 1};

    RaylibAdditions::SpeedometerClass speedometer = {{0, float(ATCPanelTexture.height), 300, 300}, 0, 200, 160, 380, 21, "km/h", WHITE, YELLOW};
    Rectangle speedButtonRect = {0, 300, 50, 50};
    RaylibAdditions::ButtonClass speedRemove = {speedButtonRect, "-10", 20, GRAY, WHITE, WHITE, 5, 1};
    speedButtonRect.x += 300 - 50;
    RaylibAdditions::ButtonClass speedAdd = {speedButtonRect, "+10", 20, GRAY, WHITE, WHITE, 5, 1};
    Rectangle speedButtonRectSmall = {50, 300, 50, 50};
    RaylibAdditions::ButtonClass speedRemoveSmall = {speedButtonRectSmall, "-1", 20, GRAY, WHITE, WHITE, 5, 1};
    speedButtonRectSmall.x += 200 - 50;
    RaylibAdditions::ButtonClass speedAddSmall = {speedButtonRectSmall, "+1", 20, GRAY, WHITE, WHITE, 5, 1};

    RaylibAdditions::SpeedometerClass brakePressure = {{300, float(ATCPanelTexture.height), 300, 300}, 0, 10, 160, 380, 11, "kPa", WHITE, RED};
    Rectangle brakePressureButtonRect = {300, 300, 50, 50};
    RaylibAdditions::ButtonClass brakePressureRemove = {brakePressureButtonRect, "-0,5", 20, GRAY, WHITE, WHITE, 5, 1};
    brakePressureButtonRect.x += 300 - 50;
    RaylibAdditions::ButtonClass brakePressureAdd = {brakePressureButtonRect, "+0,5", 20, GRAY, WHITE, WHITE, 5, 1};

    Rectangle toggleATCRect = {0, 350, 200, 50};
    RaylibAdditions::ButtonClass toggleATCButton = {toggleATCRect, "Toggle ATC", 20, GRAY, WHITE, WHITE, 5, 1};

    std::vector<std::pair<Vector2, int>> thumbWheels = {
        {{691, 21}, 0}, // STH/V-MAX
        {{712, 21}, 0},

        {{752, 21}, 0}, // length (100m)

        {{795, 21}, 0}, // tillsättningstid / brake apply time
        {{817, 21}, 0},

        {{861, 21}, 0}, // redartationstalet / deacelerationnumber (converted by some formula, locos have a guide) (bromsprocent på 76 = 061)
        {{882, 21}, 0},
        {{903, 21}, 0},

        {{949, 21}, 0}, // procentuell överskridning / procentual override, X2000 has 30% due to boggies design and tilting
    };

    ShiraNet::Sockets::TcpSocket socket(AF_INET);
    socket.connect("localhost", 1337);

    std::thread getATCDataThread{getDataThread, std::ref(socket)};

    while (!WindowShouldClose()) {
        // ATC values
        int y = 0;
        int fontSize = 10;
        int lineHeight = 14; // slightly bigger than font size for spacing
        DrawText(("ATCStatus = " + std::to_string(ATCData.ATCStatus)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("toneF1 = " + std::to_string(ATCData.toneF1)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("toneF2 = " + std::to_string(ATCData.toneF2)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("shuntingLamp = " + std::to_string(ATCData.shuntingLamp)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("ATCStatus = " + std::to_string(ATCData.ATCStatus)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("preIndicator0 = " + std::string(1, ATCData.preIndicator0)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("preIndicator1 = " + std::string(1, ATCData.preIndicator1)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("preIndicator2 = " + std::string(1, ATCData.preIndicator2)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("ATCError = " + std::to_string(ATCData.ATCError)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("BaliseError = " + std::to_string(ATCData.BaliseError)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("speeding = " + std::to_string(ATCData.speeding)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("mainIndicator0 = " + std::string(1, ATCData.mainIndicator0)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("mainIndicator1 = " + std::string(1, ATCData.mainIndicator1)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("mainIndicator2 = " + std::string(1, ATCData.mainIndicator2)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("releaseLamp = " + std::to_string(ATCData.releaseLamp)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("increaseLamp = " + std::to_string(ATCData.increaseLamp)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("dataEntryLamp = " + std::to_string(ATCData.dataEntryLamp)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("smallError = " + std::to_string(ATCData.smallError)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("requestedBrakePressure = " + std::to_string(ATCData.requestedBrakePressure)).c_str(), 1024, y, fontSize, WHITE);

        // update
        //  this button code sucks, fix it
        shuntingButton.updateState();
        releaseButton.updateState();
        increaseButton.updateState();
        stopPassageButton.updateState();
        dataEntryButton.updateState();
        speedRemove.updateState();
        speedRemoveSmall.updateState();
        speedAdd.updateState();
        speedAddSmall.updateState();
        brakePressureRemove.updateState();
        brakePressureAdd.updateState();
        toggleATCButton.updateState();

        if (toggleATCButton.state == 2) {
            if (ATCData.ATCStatus == 0)
                ATCNetworking::toggleATCPower(1, socket);
            else
                ATCNetworking::toggleATCPower(0, socket);
        }

        if (speedRemove.state == 2)
            speedometer.value -= 10;
        if (speedRemoveSmall.state == 2)
            speedometer.value -= 1;
        if (speedAdd.state == 2)
            speedometer.value += 10;
        if (speedAddSmall.state == 2)
            speedometer.value += 1;

        if (brakePressureRemove.state == 2)
            brakePressure.value -= 0.5;
        if (brakePressureAdd.state == 2)
            brakePressure.value += 0.5;

        // draw
        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexture(ATCPanelTexture, 0, 0, WHITE);
        speedometer.drawSpeedometer();
        brakePressure.drawSpeedometer();
        speedRemove.draw();
        speedRemoveSmall.draw();
        speedAdd.draw();
        speedAddSmall.draw();
        brakePressureRemove.draw();
        brakePressureAdd.draw();
        toggleATCButton.draw();

        DrawText(std::string(1, ATCData.preIndicator0).c_str(), preInd.x + (preInd.width/3.0)*0, preInd.y + preInd.height/2 - 5, 10, YELLOW);
        DrawText(std::string(1, ATCData.preIndicator1).c_str(), preInd.x + (preInd.width/3.0)*1, preInd.y + preInd.height/2 - 5, 10, YELLOW);
        DrawText(std::string(1, ATCData.preIndicator2).c_str(), preInd.x + (preInd.width/3.0)*2, preInd.y + preInd.height/2 - 5, 10, YELLOW);

        DrawText(std::string(1, ATCData.mainIndicator0).c_str(), mainInd.x + (mainInd.width/3.0)*0, mainInd.y + mainInd.height/2 - 10, 20, GREEN);
        DrawText(std::string(1, ATCData.mainIndicator1).c_str(), mainInd.x + (mainInd.width/3.0)*1, mainInd.y + mainInd.height/2 - 10, 20, GREEN);
        DrawText(std::string(1, ATCData.mainIndicator2).c_str(), mainInd.x + (mainInd.width/3.0)*2, mainInd.y + mainInd.height/2 - 10, 20, GREEN);

        EndDrawing();
    }
}