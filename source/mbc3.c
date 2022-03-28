#include "mbc3.h"
#include "utils.h"

#define SAVE_BANK   0x00

#define RTC_SECONDS 0x08
#define RTC_MINUTES 0x09
#define RTC_HOURS   0x0A
#define RTC_DAYSLOW 0x0B
#define RTC_MISC    0x0C

// the call and return wastes ten bus cycles, which is 10 microseconds DMG speed and 5 microseconds CGB speed. a 4 microsecond gap is recommended between RTC register accesses
void delayForRTC (void) {
    return;
}

// in ASM because SDCC wouldn't take no optimization for an answer
void latchRTC (void) {
    __asm__("ld	hl, #0x6000");
    __asm__("ld	(hl), #0x00");
    __asm__("ld	(hl), #0x01");
}

void haltRTC (void) {
    SWITCH_RAM(RTC_MISC);
    uint_fast8_t miscByte = _SRAM[0];
    setBit(&miscByte, 6);
    delayForRTC();
    _SRAM[0] = miscByte;
    delayForRTC();
}

void unhaltRTC (void) {
    SWITCH_RAM(RTC_MISC);
    uint_fast8_t miscByte = _SRAM[0];
    clearBit(&miscByte, 6);
    delayForRTC();
    _SRAM[0] = miscByte;
    delayForRTC();
}

uint_fast16_t readDayCounterAndRTCControl (void) {
    uint_fast16_t returnValue;
    latchRTC();

    SWITCH_RAM(RTC_DAYSLOW);
    returnValue = _SRAM[0];
    delayForRTC();

    SWITCH_RAM(RTC_MISC);
    returnValue |= _SRAM[0] << 8;
    delayForRTC();

    latchRTC();
    SWITCH_RAM(SAVE_BANK);
    return returnValue;
}

uint_fast16_t readTime (void) {
    uint_fast16_t returnValue;
    latchRTC();

    SWITCH_RAM(RTC_MINUTES);
    returnValue = _SRAM[0];
    delayForRTC();

    SWITCH_RAM(RTC_HOURS);
    returnValue |= _SRAM[0] << 8;
    delayForRTC();

    latchRTC();
    SWITCH_RAM(SAVE_BANK);
    return returnValue;   
}

void writeZeroDays (void) {
    haltRTC();

    SWITCH_RAM(RTC_DAYSLOW);
    _SRAM[0] = 0;
    delayForRTC();

    SWITCH_RAM(RTC_MISC);
    _SRAM[0] = 0; // instead of making an expensive unhaltRTC call, this conveniently clears everything desired and doesn't clear anything undesired
    delayForRTC();

    SWITCH_RAM(SAVE_BANK);
}

void writeTime (uint_fast8_t hours, uint_fast8_t minutes) {
    haltRTC();

    SWITCH_RAM(RTC_HOURS);
    _SRAM[0] = hours;
    delayForRTC();

    SWITCH_RAM(RTC_MINUTES);
    _SRAM[0] = minutes;
    delayForRTC();

    unhaltRTC();
    SWITCH_RAM(SAVE_BANK);
}
