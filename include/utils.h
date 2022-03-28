#ifndef UTILS_H
#define UTILS_H

#include "wordleboyTypes.h"

#define DAILY_WORD_COUNT 2309

void letterGuessQualitiesToChars (enum LetterGuessQuality* qualities, char* output);

void formatTwoDigitNumber (uint_fast8_t number, char* place);

void unfinishedOld (void);
void newGameInit (void);

void getByteAndBit (uint8_t* inByteLoc, uint_fast16_t inBitLoc, uint8_t** outByteLoc, uint_fast8_t* outBitLoc);
void setBit (uint8_t* byteLoc, uint_fast8_t bitLoc);
void clearBit (uint8_t* byteLoc, uint_fast8_t bitLoc);
void toggleBit (uint8_t* byteLoc, uint_fast8_t bitLoc);
bool testBit (uint8_t* byteLoc, uint_fast8_t bitLoc);

#endif // UTILS_H
