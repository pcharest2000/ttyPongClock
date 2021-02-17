#ifndef __DIGIT_H_
#define __DIGIT_H_

#include "matrix.h"
#include "utils.h"

class Digit : public Matrix {

public:
  Digit(configuration_t &config, uint8_t value, uint16_t xo, uint16_t yo);
  void Draw(uint8_t value);
  void Morph(uint8_t newValue);
  uint8_t Value();
  void DrawColon();

private:
  uint8_t _value;
  uint16_t _color;
  uint16_t xOffset;
  uint16_t yOffset;
  int animSpeed = 30;

  void drawPixel(uint16_t x, uint16_t y);
  void clrPixel(uint16_t x, uint16_t y);
  void drawFillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
  void clrLine(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2);
  void drawLine(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2);
  void drawSeg(uint8_t seg);
  void Morph2();
  void Morph3();
  void Morph4();
  void Morph5();
  void Morph6();
  void Morph7();
  void Morph8();
  void Morph9();
  void Morph0();
  void Morph1();
};

#endif // __DIGIT_H_
