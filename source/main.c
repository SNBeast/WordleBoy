#include "mbc3.h"
#include "utils.h"
#include "screens.h"
#include "words.h"
#include <gbdk/console.h>
#include <stdio.h>

const char* magic = "WORDLEBOY";

char time[6] = {0};

int main (void) {
    ENABLE_RAM;

    do {
        if (memcmp(save->magic, magic, 10)) {
            memset(save, 0, sizeof(struct SaveData));
            for (uint8_t i = 0; i < 6; i++) {
                save->guesses[i][5] = '\0';
                save->guessQualities[i][5] = '\0';
            }
            timeScreen();
            dateScreen();
            newGameInit();
            memcpy(save, magic, 10);
        }
        else {
            uint16_t dayCounterAndRTCControl = readDayCounterAndRTCControl();
            if (dayCounterAndRTCControl & 0x8000) {
                dateScreen();
            }
            else if (dayCounterAndRTCControl) {
                save->lastDayBooted = (save->lastDayBooted + dayCounterAndRTCControl) % DAILY_WORD_COUNT;
            }

            if (save->lastDayBooted != save->lastDayPlayed) {
                if (!save->finished && save->guessCount) {
                    unfinishedOld();
                }
                newGameInit();
            }
        }

        loadDailyWord();
        gameScreen();
    
        do {
            uint8_t padState = waitpad(J_SELECT);
            if ((padState & J_UP) && (padState & J_A)) {
                cls();
                puts("Delete save data?\n\nDOWN: Yes\nB: No");
                padState = waitpad(J_DOWN | J_B);
                if (padState & J_DOWN) {
                    cls();
                    puts("Are you sure you\nwant to delete your\nsave data?\n\nSTART: Yes\nB: No");
                    padState = waitpad(J_START | J_B);
                    if (padState & J_START) {
                        *(uint8_t*)save = 0; // the beginning of main will do the rest
                        cls();
                        puts("Save deleted.");
                        delay(4000);
                    }
                }
                cls();
                break;
            }
            else if (padState & J_START) {
                cls();
                uint_fast16_t hoursMinutes = readTime();
                formatTwoDigitNumber(hoursMinutes >> 8, time);
                formatTwoDigitNumber(hoursMinutes & 0xFF, time + 3);
                printf("Set time is\n%s:%s\n\n", time, time + 3);
                printf("Set Wordle index is\n%u\n\nLeft: Set time\nRight: Set day\nB: Back", save->lastDayBooted);
                
                padState = waitpad(J_LEFT | J_RIGHT | J_B);
                if (padState & J_LEFT) {
                    cls();
                    timeScreen();
                    if (hoursMinutes > readTime()) {
                        cls();
                        puts("Is it the next day?\n\nA: Yes\nB: No");
                        padState = waitpad(J_A | J_B);
                        if (padState & J_A) {
                            save->lastDayBooted = (save->lastDayBooted + 1) % DAILY_WORD_COUNT;
                        }
                    }
                }
                else if (padState & J_RIGHT) {
                    cls();
                    dateScreen();
                }
                cls();
                break;
            }
        } while (true);
    } while (true);

    #pragma save
    #pragma disable_warning 126 // unreachable code
    return 0;
    #pragma restore
}
