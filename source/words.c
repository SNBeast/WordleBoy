#include "words.h"

BANKREF_EXTERN(aWords)
BANKREF_EXTERN(bWords)
BANKREF_EXTERN(cWords)
BANKREF_EXTERN(dWords)
BANKREF_EXTERN(eWords)
BANKREF_EXTERN(fWords)
BANKREF_EXTERN(gWords)
BANKREF_EXTERN(hWords)
BANKREF_EXTERN(iWords)
BANKREF_EXTERN(jWords)
BANKREF_EXTERN(kWords)
BANKREF_EXTERN(lWords)
BANKREF_EXTERN(mWords)
BANKREF_EXTERN(nWords)
BANKREF_EXTERN(oWords)
BANKREF_EXTERN(pWords)
BANKREF_EXTERN(qWords)
BANKREF_EXTERN(rWords)
BANKREF_EXTERN(sWords)
BANKREF_EXTERN(tWords)
BANKREF_EXTERN(uWords)
BANKREF_EXTERN(vWords)
BANKREF_EXTERN(wWords)
BANKREF_EXTERN(xWords)
BANKREF_EXTERN(yWords)
BANKREF_EXTERN(zWords)
BANKREF_EXTERN(dailyWords)

char correct[6] = {' ', ' ', ' ', ' ', ' ', '\0'};
char correctCopy[5] = {' ', ' ', ' ', ' ', ' '};
char guessCopy[5] = {' ', ' ', ' ', ' ', ' '};

void loadDailyWord (void) {
    SWITCH_ROM(BANK(dailyWords));
    memcpy(correct, dailyWords + (save->lastDayBooted * 5), 5);
}

const char* getDailyWord (void) {
    return correct;
}

bool wordsMatch (const char* guess, const char* romWordToTry) {
    return !memcmp(guess, romWordToTry, 5);
}

bool wordMatchesCorrect (char* guess) {
    return wordsMatch(guess, correct);
}

void compareGuess (const char* guess, enum LetterGuessQuality* guessQualityBuffer) {
    memcpy(correctCopy, correct, 5);
    memcpy(guessCopy, guess, 5);
    for (uint_fast8_t i = 0; i < 5; i++) {
        if (guessCopy[i] == correctCopy[i]) {
            guessQualityBuffer[i] = TOTAL_HIT;
            guessCopy[i] = correctCopy[i] = ' ';
        }
    }
    for (uint_fast8_t i = 0; i < 5; i++) {
        char c = guessCopy[i];
        if (c == ' ') continue;
        for (uint_fast8_t j = 0; j < 5; j++) {
            if (c == correctCopy[j]) {
                guessQualityBuffer[i] = MISLOCATED;
                guessCopy[i] = correctCopy[j] = ' ';
                break;
            }
        }
    }
    for (uint_fast8_t i = 0; i < 5; i++) {
        if (guessCopy[i] != ' ') {
            guessQualityBuffer[i] = TOTAL_MISS;
        }
    }
}

bool guessSubmitted (const char* guess, enum LetterGuessQuality* guessQualityBuffer) {
    const uint8_t* wordList = NULL;
    uint_fast16_t wordListLength = 0;
    switch (*guess) {
        case 'A':
            SWITCH_ROM(BANK(aWords));
            wordList = aWords;
            wordListLength = aWordsSize;
            break;
        case 'B':
            SWITCH_ROM(BANK(bWords));
            wordList = bWords;
            wordListLength = bWordsSize;
            break;
        case 'C':
            SWITCH_ROM(BANK(cWords));
            wordList = cWords;
            wordListLength = cWordsSize;
            break;
        case 'D':
            SWITCH_ROM(BANK(dWords));
            wordList = dWords;
            wordListLength = dWordsSize;
            break;
        case 'E':
            SWITCH_ROM(BANK(eWords));
            wordList = eWords;
            wordListLength = eWordsSize;
            break;
        case 'F':
            SWITCH_ROM(BANK(fWords));
            wordList = fWords;
            wordListLength = fWordsSize;
            break;
        case 'G':
            SWITCH_ROM(BANK(gWords));
            wordList = gWords;
            wordListLength = gWordsSize;
            break;
        case 'H':
            SWITCH_ROM(BANK(hWords));
            wordList = hWords;
            wordListLength = hWordsSize;
            break;
        case 'I':
            SWITCH_ROM(BANK(iWords));
            wordList = iWords;
            wordListLength = iWordsSize;
            break;
        case 'J':
            SWITCH_ROM(BANK(jWords));
            wordList = jWords;
            wordListLength = jWordsSize;
            break;
        case 'K':
            SWITCH_ROM(BANK(kWords));
            wordList = kWords;
            wordListLength = kWordsSize;
            break;
        case 'L':
            SWITCH_ROM(BANK(lWords));
            wordList = lWords;
            wordListLength = lWordsSize;
            break;
        case 'M':
            SWITCH_ROM(BANK(mWords));
            wordList = mWords;
            wordListLength = mWordsSize;
            break;
        case 'N':
            SWITCH_ROM(BANK(nWords));
            wordList = nWords;
            wordListLength = nWordsSize;
            break;
        case 'O':
            SWITCH_ROM(BANK(oWords));
            wordList = oWords;
            wordListLength = oWordsSize;
            break;
        case 'P':
            SWITCH_ROM(BANK(pWords));
            wordList = pWords;
            wordListLength = pWordsSize;
            break;
        case 'Q':
            SWITCH_ROM(BANK(qWords));
            wordList = qWords;
            wordListLength = qWordsSize;
            break;
        case 'R':
            SWITCH_ROM(BANK(rWords));
            wordList = rWords;
            wordListLength = rWordsSize;
            break;
        case 'S':
            SWITCH_ROM(BANK(sWords));
            wordList = sWords;
            wordListLength = sWordsSize;
            break;
        case 'T':
            SWITCH_ROM(BANK(tWords));
            wordList = tWords;
            wordListLength = tWordsSize;
            break;
        case 'U':
            SWITCH_ROM(BANK(uWords));
            wordList = uWords;
            wordListLength = uWordsSize;
            break;
        case 'V':
            SWITCH_ROM(BANK(vWords));
            wordList = vWords;
            wordListLength = vWordsSize;
            break;
        case 'W':
            SWITCH_ROM(BANK(wWords));
            wordList = wWords;
            wordListLength = wWordsSize;
            break;
        case 'X':
            SWITCH_ROM(BANK(xWords));
            wordList = xWords;
            wordListLength = xWordsSize;
            break;
        case 'Y':
            SWITCH_ROM(BANK(yWords));
            wordList = yWords;
            wordListLength = yWordsSize;
            break;
        case 'Z':
            SWITCH_ROM(BANK(zWords));
            wordList = zWords;
            wordListLength = zWordsSize;
            break;
    }

    if (wordList) {
        const uint8_t* wordListEnd = wordList + wordListLength;
        for (const uint8_t* currentWord = wordList; currentWord < wordListEnd; currentWord += 5) {
            if (wordsMatch(guess, currentWord)) {
                compareGuess(guess, guessQualityBuffer);
                return true;
            }
        }
    }

    SWITCH_ROM(BANK(dailyWords));
    wordList = dailyWords;
    wordListLength = dailyWordsSize;

    const uint8_t* wordListEnd = wordList + wordListLength;
    for (const uint8_t* currentWord = wordList; currentWord < wordListEnd; currentWord += 5) {
        if (wordsMatch(guess, currentWord)) {
            compareGuess(guess, guessQualityBuffer);
            return true;
        }
    }

    return false;
}
