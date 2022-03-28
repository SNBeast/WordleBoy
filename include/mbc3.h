#ifndef MBC3_H
#define MBC3_H

#include "wordleboyTypes.h"

uint_fast16_t readDayCounterAndRTCControl (void);
uint_fast16_t readTime (void);
void writeZeroDays (void);
void writeTime (uint_fast8_t hours, uint_fast8_t minutes);

#endif // MBC3_H
