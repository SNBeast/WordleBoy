#ifndef WORDLEBOYTYPES_H
#define WORDLEBOYTYPES_H

#include <gb/gb.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define save ((struct SaveData*)_SRAM)

struct SaveData {
    char magic[10]; //"WORDLEBOY"
    uint16_t totalPlayed;
    uint16_t totalWins;
    uint16_t currentStreak;
    uint16_t maxStreak;
    uint16_t scoreCounts[6];

    uint16_t lastDayBooted;
    uint16_t lastDayPlayed;
    bool finished;
    char guesses[6][6];
    enum LetterGuessQuality guessQualities[6][6];
    uint8_t guessCount;
};

enum LetterGuessQuality {
    TOTAL_MISS = 0,
    MISLOCATED,
    TOTAL_HIT
};

#endif // WORDLEBOYTYPES_H
