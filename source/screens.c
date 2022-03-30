#include "screens.h"
#include "mbc3.h"
#include "utils.h"
#include "words.h"
#include <gbdk/console.h>
#include <ctype.h>
#include <stdio.h>

#define GETS_LENGTH 40

#define max(a,b) (((a) > (b)) ? (a) : (b))

const char* invalidInput = "Invalid input.";
const char* howManyDays = "How many days has\nit been since\nJune 19th, 2021?\n";
const char* whatHourIsIt = "What hour is it?\n(0-23)\n";
const char* whatMinuteIsIt = "What minute is it?\n(0-59)\n";
const char* soItsAbout = "So, it's about\n%s:%s?\n\nA: Confirm\nB: Revise";
const char* soWordleIndex = "So, Wordle index\n%u?\n\nA: Confirm\nB: Revise";
const char* playedWinPercentage = "\n%u Played\n%u Win Percentage";
const char* currentMaxStreak = "\n%u Current Streak\n%u Max Streak";
const char* oneTwoThree = "\n1: %u\n2: %u\n3: %u";
const char* fourFiveSix = "\n4: %u\n5: %u\n6: %u";
const char* twoStrings = "%s  %s\n";

char getsInput[GETS_LENGTH] = {0};

uint_fast8_t getMaxTwoDigitNumber (const char* prompt, uint_fast8_t max) {
    do {
        puts(prompt);
        gets(getsInput);
        uint_fast8_t len = strlen(getsInput);
        if (len && len <= 2) {
            bool continueCondition = false;
            for (int i = 0; i < len; i++) {
                if (!isdigit(getsInput[i])) {
                    continueCondition = true;
                    break;
                }
            }
            if (!continueCondition) {
                uint_fast8_t returnValue = atoi(getsInput);
                if (returnValue <= max) {
                    return returnValue;
                }
            }
        }
        cls();
        puts(invalidInput);
    } while (true);
}

uint_fast16_t getDayNumber () {
    do {
        puts(howManyDays);
        gets(getsInput);
        uint_fast8_t len = strlen(getsInput);
        if (len) {
            bool continueCondition = false;
            for (int i = 0; i < len; i++) {
                if (!isdigit(getsInput[i])) {
                    continueCondition = true;
                    break;
                }
            }
            if (!continueCondition) {
                uint_fast32_t returnValue = atol(getsInput); // atoi advertises returning an int but can only handle one byte instead of two, so this'll probably fail before it should too, and there's no unsigned variant
                return returnValue % DAILY_WORD_COUNT;
            }
        }
        cls();
        puts(invalidInput);
    } while (true);
}

void timeScreen (void) {
    do {
        uint_fast8_t hourValue = getMaxTwoDigitNumber(whatHourIsIt, 23);
        cls();
        uint_fast8_t minuteValue = getMaxTwoDigitNumber(whatMinuteIsIt, 59);
        cls();

        formatTwoDigitNumber(hourValue, getsInput);
        formatTwoDigitNumber(minuteValue, getsInput + 3);
        printf(soItsAbout, getsInput, getsInput + 3);
        uint_fast8_t padState = waitpad(J_A | J_B);
        cls();
        if (padState & J_A) {
            writeTime(hourValue, minuteValue);
            return;
        }
    } while (true);
}

void dateScreen (void) {
    do {
        uint_fast16_t dayNumber = getDayNumber();
        cls();

        printf(soWordleIndex, dayNumber);
        uint_fast8_t padState = waitpad(J_A | J_B);
        cls();
        if (padState & J_A) {
            save->lastDayBooted = dayNumber;
            writeZeroDays();
            return;
        }
    } while (true);
}

// this will have gameScreen's graphics still on it
void resultScreen (void) {
    printf(playedWinPercentage, save->totalPlayed, ((uint32_t)(save->totalWins) * 100)/save->totalPlayed);
    printf(currentMaxStreak, save->currentStreak, save->maxStreak);
    printf(oneTwoThree, save->scoreCounts[0], save->scoreCounts[1], save->scoreCounts[2]);
    printf(fourFiveSix, save->scoreCounts[3], save->scoreCounts[4], save->scoreCounts[5]);
}

void gameScreen (void) {
    do {
        for (int i = 0; i < 6; i++) {
            printf(twoStrings, save->guesses[i], save->guessQualities[i]);
        }
        if (save->finished && save->currentStreak == 0) {
            puts(getDailyWord());
        }
        if (save->finished) {
            resultScreen();
            return;
        }
        gets(getsInput);
        uint_fast8_t len = strlen(getsInput);
        if (len == 5) {
            bool continueCondition = false;
            for (int i = 0; i < len; i++) {
                if (!isalpha(getsInput[i])) {
                    continueCondition = true;
                    break;
                }
                if (islower(getsInput[i])) {
                    getsInput[i] = toupper(getsInput[i]);
                }
            }
            if (!continueCondition && guessSubmitted(getsInput, getsInput + 6)) {
                uint_fast8_t guessIndex = save->guessCount;
                memcpy(save->guesses[guessIndex], getsInput, 5);
                letterGuessQualitiesToChars(getsInput + 6, save->guessQualities[guessIndex]);
                save->guessCount = guessIndex + 1;

                save->lastDayPlayed = save->lastDayBooted;

                if (wordMatchesCorrect(getsInput)) {
                    save->finished = true;
                    save->currentStreak++;
                    save->maxStreak = max(save->currentStreak, save->maxStreak);
                    save->scoreCounts[guessIndex]++;
                    save->totalPlayed++;
                    save->totalWins++;
                }
                else if (guessIndex + 1 == 6) {
                    save->finished = true;
                    save->currentStreak = 0;
                    save->totalPlayed++;
                }
            }
        }
        cls();
    } while (true);
}
