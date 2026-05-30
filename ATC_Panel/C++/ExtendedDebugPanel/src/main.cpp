#include <RaylibAdditions.hpp>
#include <ShiraNet.hpp>
#include <raylib.h>
#include <iostream>

#include "ATCData.hpp"
#include "networking.hpp"
#include "drawing.hpp"

ATCReturnData ReceivedATCData;

void getDataThread(ShiraNet::Sockets::TcpSocket &socket) {
    while (true) { // [taskig] use interval
        auto newData = ATCNetworking::getATCData(socket);
        if (newData.has_value()) {
            ReceivedATCData = newData.value();
        }
    }
}

int main() {
    RaylibAdditions::WindowClass window{"ATC_Panel_Extended_Debug", 1200, 500}; // read screen size from config later

    SetTargetFPS(60);
    SetWindowMonitor(0);
    SetExitKey(KEY_NULL);

    const std::string resPath = "../../../res";
    InitAudioDevice();
    Sound ATC1 = LoadSound((resPath + "/f1.wav").c_str()); // Better f1 tone // 1. f1 med 2,5 kHz ± 20 %. f1 aktiveras endast vid ATC-larm (verkligt eller simulerat) och är helt oberoende av om ATC-systemets matningsdon fungerar eller inte. Ljudstyrkan hos f1 kan inte regleras.
    Sound ATC2 = LoadSound((resPath + "/f2.wav").c_str()); // f2 med 400 Hz ± 10 % fyrkantvåg. f2 är styrbar från datorerna under normal drift. Den aktiveras dessutom vid ATC-larm och är härvid oberoende av om ATC-systemets matningsdon fungerar eller inte. Ljudstyrkan är reglerbar med en potentiometer på panelen.
    
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

    ATCPanelDrawing ATCDrawing;

    ShiraNet::Sockets::TcpSocket socket(AF_INET);

    bool connected = false;
    while (connected == 0) { // this should be remade in some better form directly in shiranet
        try {
            socket.connect("localhost", 1337);
            connected = true;
        } catch (...) {
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Could not connect to ATC Dator", 0, 0, 50, WHITE);
        EndDrawing();
    }

    std::thread getATCDataThread{getDataThread, std::ref(socket)};

    while (!WindowShouldClose()) {
        // update

        ATCDrawing.updateButtons(true);

        if (ATCDrawing.toggleATCButton.state == 2) {
            if (ReceivedATCData.ATCStatus == 0)
                ATCNetworking::toggleATCPower(1, socket);
            else
                ATCNetworking::toggleATCPower(0, socket);
        }

        // draw
        BeginDrawing();
        ClearBackground(BLACK);

                // ATC values
        int y = 0;
        int fontSize = 10;
        int lineHeight = 14; // slightly bigger than font size for spacing
        DrawText(("ATCStatus = " + std::to_string(ReceivedATCData.ATCStatus)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("toneF1 = " + std::to_string(ReceivedATCData.toneF1)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("toneF2 = " + std::to_string(ReceivedATCData.toneF2)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("shuntingLamp = " + std::to_string(ReceivedATCData.shuntingLamp)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("ATCStatus = " + std::to_string(ReceivedATCData.ATCStatus)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("preIndicator0 = " + std::string(1, ReceivedATCData.preIndicator0)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("preIndicator1 = " + std::string(1, ReceivedATCData.preIndicator1)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("preIndicator2 = " + std::string(1, ReceivedATCData.preIndicator2)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("ATCError = " + std::to_string(ReceivedATCData.ATCError)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("BaliseError = " + std::to_string(ReceivedATCData.BaliseError)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("speeding = " + std::to_string(ReceivedATCData.speeding)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("mainIndicator0 = " + std::string(1, ReceivedATCData.mainIndicator0)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("mainIndicator1 = " + std::string(1, ReceivedATCData.mainIndicator1)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("mainIndicator2 = " + std::string(1, ReceivedATCData.mainIndicator2)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("releaseLamp = " + std::to_string(ReceivedATCData.releaseLamp)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("increaseLamp = " + std::to_string(ReceivedATCData.increaseLamp)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("dataEntryLamp = " + std::to_string(ReceivedATCData.dataEntryLamp)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("smallError = " + std::to_string(ReceivedATCData.smallError)).c_str(), 1024, y, fontSize, WHITE);
        y += lineHeight;
        DrawText(("requestedBrakePressure = " + std::to_string(ReceivedATCData.requestedBrakePressure)).c_str(), 1024, y, fontSize, WHITE);

        ATCDrawing.drawButtons();
        char indicators[6] = {
            ReceivedATCData.preIndicator0,
            ReceivedATCData.preIndicator1,
            ReceivedATCData.preIndicator2,
            ReceivedATCData.mainIndicator0,
            ReceivedATCData.mainIndicator1,
            ReceivedATCData.mainIndicator2
        };
        ATCDrawing.drawIndicators(indicators);
        EndDrawing();
    }
}