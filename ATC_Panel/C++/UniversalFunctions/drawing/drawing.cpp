#include "drawing.hpp"

#include <raylib.h>

void ATCPanelDrawing::updateButtons(bool debugButtons) {
    //  this button code sucks, fix it
    shuntingButton.updateState();
    releaseButton.updateState();
    increaseButton.updateState();
    stopPassageButton.updateState();
    dataEntryButton.updateState();

    if (debugButtons) {
        speedRemove.updateState();
        speedRemoveSmall.updateState();
        speedAdd.updateState();
        speedAddSmall.updateState();
        brakePressureRemove.updateState();
        brakePressureAdd.updateState();
        toggleATCButton.updateState();

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
    }

}

void ATCPanelDrawing::drawButtons(bool debugButtons) {
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
}

void ATCPanelDrawing::drawIndicators(char indicators[6]) {

        DrawText(std::string(1, indicators[0]).c_str(), preInd.x + (preInd.width/3.0)*0, preInd.y + preInd.height/2 - 5, 10, YELLOW);
        DrawText(std::string(1, indicators[1]).c_str(), preInd.x + (preInd.width/3.0)*1, preInd.y + preInd.height/2 - 5, 10, YELLOW);
        DrawText(std::string(1, indicators[2]).c_str(), preInd.x + (preInd.width/3.0)*2, preInd.y + preInd.height/2 - 5, 10, YELLOW);

        DrawText(std::string(1, indicators[3]).c_str(), mainInd.x + (mainInd.width/3.0)*0, mainInd.y + mainInd.height/2 - 10, 20, GREEN);
        DrawText(std::string(1, indicators[4]).c_str(), mainInd.x + (mainInd.width/3.0)*1, mainInd.y + mainInd.height/2 - 10, 20, GREEN);
        DrawText(std::string(1, indicators[5]).c_str(), mainInd.x + (mainInd.width/3.0)*2, mainInd.y + mainInd.height/2 - 10, 20, GREEN);
}