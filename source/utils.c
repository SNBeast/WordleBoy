#include "utils.h"
#include "words.h"

void letterGuessQualitiesToChars (enum LetterGuessQuality* qualities, char* output) {
    for (uint_fast8_t i = 0; i < 5; i++) {
        switch (qualities[i]) {
            case TOTAL_MISS:
                output[i] = '-';
                break;
            case MISLOCATED:
                output[i] = '*';
                break;
            case TOTAL_HIT:
                output[i] = '+';
                break;
        }
    }
}

void formatTwoDigitNumber (uint_fast8_t number, char* place) {
    if (number < 10) {
        *place = '0';
        place++;
    }
    itoa(number, place, 10);
}

void unfinishedOld (void) {
    (save->totalPlayed)++;
    save->currentStreak = 0;
}

void newGameInit (void) {
    for (uint8_t i = 0; i < 6; i++) {
        memset(save->guesses[i], '_', 5);
        memset(save->guessQualities[i], ' ', 5);
    }
    save->guessCount = 0;
    save->finished = false;
    if (save->lastDayPlayed + 1 != save->lastDayBooted) {
        save->currentStreak = 0;
    }
}

void getByteAndBit (uint8_t* inByteLoc, uint_fast16_t inBitLoc, uint8_t** outByteLoc, uint_fast8_t* outBitLoc) {
    *outByteLoc = inByteLoc + (inBitLoc >> 3);
    *outBitLoc = inBitLoc & 0x7;
}

void setBit (uint8_t* byteLoc, uint_fast8_t bitLoc) {
    *byteLoc |= (uint8_t)(1 << bitLoc);
}

void clearBit (uint8_t* byteLoc, uint_fast8_t bitLoc) {
    *byteLoc &= ~(uint8_t)(1 << bitLoc);
}

void toggleBit (uint8_t* byteLoc, uint_fast8_t bitLoc) {
    *byteLoc ^= (uint8_t)(1 << bitLoc);
}

bool testBit (uint8_t* byteLoc, uint_fast8_t bitLoc) {
    return *byteLoc & (uint8_t)(1 << bitLoc);
}
