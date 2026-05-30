#pragma once

#include <raylib.h>
#include <RaylibAdditions.hpp>
#include <string>

class ATCPanelDrawing {
    public:
    Texture2D ATCPanelTexture;
    Rectangle preInd = {61, 28, 59, 24};
    Rectangle mainInd = {234, 23, 75, 30};
    Rectangle startup = {0, 64, 200, 50};
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

    RaylibAdditions::SpeedometerClass speedometer = {{0, 64, 300, 300}, 0, 200, 160, 380, 21, "km/h", WHITE, YELLOW};
    Rectangle speedRemoveRect = {0, 300, 50, 50};
    RaylibAdditions::ButtonClass speedRemove = {speedRemoveRect, "-10", 20, GRAY, WHITE, WHITE, 5, 1};
    Rectangle speedAddRect = {250, 300, 50, 50};
    RaylibAdditions::ButtonClass speedAdd = {speedAddRect, "+10", 20, GRAY, WHITE, WHITE, 5, 1};
    Rectangle speedButtonRectSmall = {50, 300, 50, 50};
    RaylibAdditions::ButtonClass speedRemoveSmall = {speedButtonRectSmall, "-1", 20, GRAY, WHITE, WHITE, 5, 1};
    Rectangle speedAddSmallRect = {200, 300, 50, 50};
    RaylibAdditions::ButtonClass speedAddSmall = {speedAddSmallRect, "+1", 20, GRAY, WHITE, WHITE, 5, 1};

    RaylibAdditions::SpeedometerClass brakePressure = {{300, 64, 300, 300}, 0, 10, 160, 380, 11, "kPa", WHITE, RED};
    Rectangle removeBrakePressureButtonRect = {300, 300, 50, 50};
    RaylibAdditions::ButtonClass brakePressureRemove = {removeBrakePressureButtonRect, "-0,5", 20, GRAY, WHITE, WHITE, 5, 1};
    Rectangle addBrakePressureButtonRect = {500, 300, 50, 50};
    RaylibAdditions::ButtonClass brakePressureAdd = {addBrakePressureButtonRect, "+0,5", 20, GRAY, WHITE, WHITE, 5, 1};

    Rectangle toggleATCRect = {0, 350, 200, 50};
    RaylibAdditions::ButtonClass toggleATCButton = {toggleATCRect, "Toggle ATC", 20, GRAY, WHITE, WHITE, 5, 1};

    ATCPanelDrawing() { ATCPanelTexture = LoadTexture("../../../res/cleanATC.png"); } // should be ./ when built for "release" or packaged, also adjust for windows, also use filesystem path for ease of use
    void updateButtons(bool debugButtons = false);
    void drawButtons(bool debugButtons = false);
    void drawIndicators(char indicators[6]);
};