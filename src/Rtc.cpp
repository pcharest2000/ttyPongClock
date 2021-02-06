#include "Rtc.h"

CRTC::CRTC() {
  _nextUpdate = 0;
  _updateInterval = 1000;
  update();
  tmmPrev = tmm;
}
CRTC::CRTC(uint32_t updateInterval) {
  _updateInterval = updateInterval;
  _nextUpdate = 0;
  update();
  tmmPrev = tmm;
}

void CRTC::begin(uint32_t updateInteval) {
  _updateInterval = updateInteval;
  _nextUpdate = 0;
  update();
  tmmPrev = tmm;
 
}

uint32_t SmallTimeGetMicroSec(void) {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_usec;
}
uint32_t getMillis(void){
  return SmallTimeGetMicroSec()/1000;
}
uint32_t CRTC::getCounter(){
time_t t =time(NULL);
  return t;
}
bool CRTC::update() {
  uint32_t ms = getMillis();
  if (_nextUpdate > ms) {
    return false;
 }
  _nextUpdate = ms + _updateInterval;
  struct timeval tv;
  // struct timezone tz;
  gettimeofday(&tv, NULL);
  uint32_t time = tv.tv_sec;
  tmm.second = time % 60;
  time /= 60;
  tmm.minute = time % 60;
  time /= 60;
  tmm.hour = time % 24;
  //cout<<"M: "<<(uint32_t) tmm.minute<<" S: "<<(uint32_t) tmm.second<<endl;
  if(tmmPrev.minute!=tmm.minute){
    tmmPrevCopy=tmm;
    tmmPrev=tmm;
    return true;
  }
  return false;
}
void CRTC::updateNow() {
  struct timeval tv;
  // struct timezone tz;
  gettimeofday(&tv, NULL);
  uint32_t time = tv.tv_sec;
  time = time + _secOffset;
  tmm.second = time % 60;
  time /= 60;
  tmm.minute = time % 60;
  time /= 60;
  tmm.hour = time % 24;
}

void CRTC::updatePrevDigits() {
  prevDigits.hourDigit = (tmmPrevCopy.hour % 10);
  prevDigits.hourTenth = (tmmPrevCopy.hour / 10);
  prevDigits.minDigit = (tmmPrevCopy.minute % 10);
  prevDigits.minTenth = (tmmPrevCopy.minute / 10);
}

void CRTC::updateCurrentDigits() {
  currentDigits.hourDigit = (tmm.hour % 10);
  currentDigits.hourTenth = (tmm.hour / 10);
  currentDigits.minDigit = (tmm.minute % 10);
  currentDigits.minTenth = (tmm.minute / 10);
}
void CRTC::updateAllDigits(){
  updatePrevDigits();
  updateCurrentDigits();
}
void CRTC::incrementMin() { _secOffset += 60; }
void CRTC::decrementMin() { _secOffset -= 60; }
void CRTC::incrementHour() { _secOffset += 3600; }
void CRTC::decrementHour() { _secOffset -= 3600; }

//CRTC rtc = CRTC();
// Global object
