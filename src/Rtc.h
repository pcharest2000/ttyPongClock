#ifndef RTC_H
#define RTC_H

#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
typedef struct {
  uint8_t pm; // AM: 0, PM: 1
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
} tm_t;

typedef struct {
  uint8_t hourTenth;
  uint8_t hourDigit;
  uint8_t minTenth;
  uint8_t minDigit;
} Digits_S;

class CRTC {
public:
  CRTC();
  CRTC(uint32_t updateInterval);
  void begin(uint32_t updateInteval);
  bool update();    // Updates the time at the given interval returns true if
                    // minutes changed
  void updateNow(); // Updates the time at the given interval returns true if
                    // minutes changed
  void updatePrevDigits(); // Decompose the time in digits
  void updateCurrentDigits();
  void updateAllDigits();
  uint32_t getCounter();
  tm_t tmm;         // Current time of the Rtc
  tm_t tmmPrev;     // To coompare when the time was changed
  tm_t tmmPrevCopy; // A copy of the prev time used for animation
  Digits_S prevDigits;
  Digits_S currentDigits;
  uint8_t hour(void) {
    update();
    return tmm.hour;
  }
  uint8_t minute(void) {
    update();
    return tmm.minute;
  }
  uint8_t second(void) {
    update();
    return tmm.second;
  }
  void incrementMin(void);
  void incrementHour(void);
  void decrementMin(void);
  void decrementHour(void);

private:
  uint32_t _updateInterval;
  uint32_t _nextUpdate;
  uint32_t _secOffset;
};

extern CRTC rtc;
#endif
