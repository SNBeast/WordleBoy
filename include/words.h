#ifndef WORDS_H
#define WORDS_H

#include "wordleboyTypes.h"

extern const uint8_t aWords[];
extern const uint8_t bWords[];
extern const uint8_t cWords[];
extern const uint8_t dWords[];
extern const uint8_t eWords[];
extern const uint8_t fWords[];
extern const uint8_t gWords[];
extern const uint8_t hWords[];
extern const uint8_t iWords[];
extern const uint8_t jWords[];
extern const uint8_t kWords[];
extern const uint8_t lWords[];
extern const uint8_t mWords[];
extern const uint8_t nWords[];
extern const uint8_t oWords[];
extern const uint8_t pWords[];
extern const uint8_t qWords[];
extern const uint8_t rWords[];
extern const uint8_t sWords[];
extern const uint8_t tWords[];
extern const uint8_t uWords[];
extern const uint8_t vWords[];
extern const uint8_t wWords[];
extern const uint8_t xWords[];
extern const uint8_t yWords[];
extern const uint8_t zWords[];
extern const uint8_t dailyWords[];

extern const uint_fast16_t aWordsSize;
extern const uint_fast16_t bWordsSize;
extern const uint_fast16_t cWordsSize;
extern const uint_fast16_t dWordsSize;
extern const uint_fast16_t eWordsSize;
extern const uint_fast16_t fWordsSize;
extern const uint_fast16_t gWordsSize;
extern const uint_fast16_t hWordsSize;
extern const uint_fast16_t iWordsSize;
extern const uint_fast16_t jWordsSize;
extern const uint_fast16_t kWordsSize;
extern const uint_fast16_t lWordsSize;
extern const uint_fast16_t mWordsSize;
extern const uint_fast16_t nWordsSize;
extern const uint_fast16_t oWordsSize;
extern const uint_fast16_t pWordsSize;
extern const uint_fast16_t qWordsSize;
extern const uint_fast16_t rWordsSize;
extern const uint_fast16_t sWordsSize;
extern const uint_fast16_t tWordsSize;
extern const uint_fast16_t uWordsSize;
extern const uint_fast16_t vWordsSize;
extern const uint_fast16_t wWordsSize;
extern const uint_fast16_t xWordsSize;
extern const uint_fast16_t yWordsSize;
extern const uint_fast16_t zWordsSize;
extern const uint_fast16_t dailyWordsSize;

void loadDailyWord (void);
const char* getDailyWord (void);
bool wordMatchesCorrect (char* guess);
bool guessSubmitted (char* guess, enum LetterGuessQuality* guessQualityBuffer);

#endif // WORDS_H
