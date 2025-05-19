void turnOffAll() {
    ATCReturn.ATCError = false;
    ATCReturn.toneF1 = false;
    ATCReturn.toneF2 = false;
    ATCReturn.shuntingLamp = false;
    ATCReturn.preIndicator0 = ' ';
    ATCReturn.preIndicator1 = ' ';
    ATCReturn.preIndicator2 = ' ';
    ATCReturn.ATCError = false;
    ATCReturn.BaliseError = false;
    ATCReturn.speeding = false;
    ATCReturn.mainIndicator0 = ' ';
    ATCReturn.mainIndicator1 = ' ';
    ATCReturn.mainIndicator2 = ' ';
    ATCReturn.releaseLamp = false;
    ATCReturn.increaseLamp = false;
    ATCReturn.dataEntryLamp = false;
    ATCReturn.smallError = false;
}

void turnOnAll() {
    ATCReturn.ATCError = true;
    ATCReturn.toneF1 = true;
    ATCReturn.toneF2 = true;
    ATCReturn.shuntingLamp = true;
    ATCReturn.preIndicator0 = '8';
    ATCReturn.preIndicator1 = '8';
    ATCReturn.preIndicator2 = '8';
    ATCReturn.ATCError = true;
    ATCReturn.BaliseError = true;
    ATCReturn.speeding = true;
    ATCReturn.mainIndicator0 = '8';
    ATCReturn.mainIndicator1 = '8';
    ATCReturn.mainIndicator2 = '8';
    ATCReturn.releaseLamp = true;
    ATCReturn.increaseLamp = true;
    ATCReturn.dataEntryLamp = true;
    ATCReturn.smallError = true;
}