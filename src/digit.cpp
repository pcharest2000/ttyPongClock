#include "digit.h"

const uint8_t sA = 0;
const uint8_t sB = 1;
const uint8_t sC = 2;
const uint8_t sD = 3;
const uint8_t sE = 4;
const uint8_t sF = 5;
const uint8_t sG = 6;
const int segHeight = 6;
const int segWidth = segHeight;
const int transDelay = 100000;

uint8_t digitBits[] = {
    0B11111100, // 0 ABCDEF--
    0B01100000, // 1 -BC-----
    0B11011010, // 2 AB-DE-G-
    0B11110010, // 3 ABCD--G-
    0B01100110, // 4 -BC--FG-
    0B10110110, // 5 A-CD-FG-
    0B10111110, // 6 A-CDEFG-
    0B11100000, // 7 ABC-----
    0B11111110, // 8 ABCDEFG-
    0B11110110, // 9 ABCD_FG-
};

// uint8_t sunBitmap[] {
//  B100100100,
//  B010001000,
//  B001110000,
//  B101110100,
//  B001110000,
//  B010001000,
//  B100100100
//};

uint16_t black;

Digit::Digit(configuration_t &config, uint8_t value, uint16_t xo, uint16_t yo)
    : Matrix(config) {
  _value = value;
  xOffset = xo;
  yOffset = yo;
  //  = color;
}

uint8_t Digit::Value() { return _value; }
void Digit::clrPixel(uint16_t x, uint16_t y) {
  clrPix(xOffset + x, y + yOffset);
}
void Digit::drawPixel(uint16_t x, uint16_t y) {
  setPix(xOffset + x, y + yOffset);
}

void Digit::drawLine(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2) {
  Matrix::drawLine(xOffset + x, (y + yOffset), xOffset + x2, (y2 + yOffset));
}

void Digit::clrLine(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2) {
  Matrix::clrLine(xOffset + x, (y + yOffset), xOffset + x2, (y2 + yOffset));
}
void Digit::drawFillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
  Matrix::drawFillRect(xOffset + x, (y + yOffset), w, h);
}

void Digit::DrawColon() {
  // Colon is drawn to the left of this digit
  Matrix::drawFillRect(-3, segHeight - 1, 2, 2);
  Matrix::drawFillRect(-3, segHeight + 1 + 3, 2, 2);
}

void Digit::drawSeg(uint8_t seg) {
  switch (seg) {
  case sD:
    drawLine(1, segHeight * 2 + 2, segWidth, segHeight * 2 + 2);
    break;
  case sC:
    drawLine(segWidth + 1, segHeight * 2 + 1, segWidth + 1, segHeight + 2);
    break;
  case sB:
    drawLine(segWidth + 1, 1, segWidth + 1, segHeight);
    break;
  case sA:
    drawLine(1, 0, segWidth, 0);
    break;
  case sF:
    drawLine(0, 1, 0, segHeight);
    break;
  case sE:
    drawLine(0, segHeight * 2 + 1, 0, segHeight + 2);
    break;
  case sG:
    drawLine(1, segHeight + 1, segWidth, segHeight + 1);
    break;
  }
}

void Digit::Draw(uint8_t value) {
  uint8_t pattern = digitBits[value];
  if (bitRead(pattern, 7))
    drawSeg(sA);
  if (bitRead(pattern, 6))
    drawSeg(sB);
  if (bitRead(pattern, 5))
    drawSeg(sC);
  if (bitRead(pattern, 4))
    drawSeg(sD);
  if (bitRead(pattern, 3))
    drawSeg(sE);
  if (bitRead(pattern, 2))
    drawSeg(sF);
  if (bitRead(pattern, 1))
    drawSeg(sG);
  _value = value;

  Matrix::draw();
}

void Digit::Morph2() {
  // TWO
  for (int i = 0; i <= segWidth; i++) {
    if (i < segWidth) {
      drawPixel(segWidth - i, 0);
      drawPixel(segWidth - i, segHeight + 1);
      drawPixel(segWidth - i, segHeight * 2 + 2);
    }

    drawLine(segWidth + 0 - i, segHeight * 2 + 1, segWidth + 0 - i,
             segHeight + 2);
    clrLine(segWidth + 1 - i, segHeight * 2 + 1, segWidth + 1 - i,
            segHeight + 2);
    usleep(transDelay);
    Matrix::draw();
    // delay(animSpeed);
  }
}

void Digit::Morph3() {
  // THREE
  for (int i = 0; i <= segWidth; i++) {
    clrLine(i, segHeight * 2 + 1, i, segHeight + 2);
    drawLine(1 + i, segHeight * 2 + 1, 1 + i, segHeight + 2);
    usleep(transDelay);
    Matrix::draw();
    // delay(animSpeed);
  }
}

void Digit::Morph4() {
  // FOUR
  for (int i = 0; i < segWidth; i++) {
    clrPixel(segWidth - i, 0);          // Erase A
    drawPixel(0, 1 + i);                // Draw as F
    clrPixel(1 + i, segHeight * 2 + 2); // Erase D
    usleep(transDelay);
    Matrix::draw();
    // delay(animSpeed);
  }
}

void Digit::Morph5() {
  // FIVE
  for (int i = 0; i < segWidth; i++) {
    clrPixel(segWidth + 1, 1 + i);              // Erase B
    drawPixel(segWidth - i, 0);                 // Draw as A
    drawPixel(segWidth - i, segHeight * 2 + 2); // Draw D
    usleep(transDelay);
    Matrix::draw();
    // delay(animSpeed);
  }
}

void Digit::Morph6() {
  // SIX
  for (int i = 0; i <= segWidth; i++) {
    // Move C right to left
    drawLine(segWidth - i, segHeight * 2 + 1, segWidth - i, segHeight + 2);
    if (i > 0)
      clrLine(segWidth + 1 - i, segHeight * 2 + 1, segWidth + 1 - i,
              segHeight + 2);
    usleep(transDelay);
    Matrix::draw();
    // delay(animSpeed);
  }
}

void Digit::Morph7() {
  // SEVEN
  for (int i = 0; i <= segWidth; i++) {
    // Move E left to right
    drawLine(1 + i, segHeight * 2 + 1, 1 + i, segHeight + 2);
    clrLine(i, segHeight * 2 + 1, i, segHeight + 2);

    // // Move F left to right
    drawLine(1 + i, 1, 1 + i, segHeight);
    clrLine(0 + i, 1, 0 + i, segHeight);

    // Erase D and G gradually
    clrPixel(1 + i, segHeight * 2 + 2); // D
    clrPixel(1 + i, segHeight + 1);     // G
    usleep(transDelay);
    Matrix::draw();
  }
}

void Digit::Morph8() {
  // EIGHT
  for (int i = 0; i <= segWidth; i++) {
    // * // Move B right to left
    drawLine(segWidth - i, 1, segWidth - i, segHeight);
    if (i > 0)
      clrLine(segWidth + 1 - i, 1, segWidth + 1 - i, segHeight);

    // Move C right to left
    drawLine(segWidth - i, segHeight * 2 + 1, segWidth - i, segHeight + 2);
    if (i > 0)
      clrLine(segWidth + 1 - i, segHeight * 2 + 1, segWidth + 1 - i,
              segHeight + 2);

    // // Gradually draw D and G
    if (i < segWidth) {
      drawPixel(segWidth - i, segHeight * 2 + 2);
      drawPixel(segWidth - i, segHeight + 1);
    } //   drawPixel(segWidth - i, 0);             // D
    //   drawPixel(segWidth - i, segHeight + 1); // G
    // }
    usleep(transDelay);
    Matrix::draw();
  }
}

void Digit::Morph9() {
  // NINE
  for (int i = 0; i <= segWidth; i++) {
    // Move E left to right
    drawLine(1 + i, segHeight * 2 + 1, 1 + i, segHeight + 2);
    clrLine(i, segHeight * 2 + 1, i, segHeight + 2);
    usleep(transDelay);
    Matrix::draw();
  }
}

void Digit::Morph0() {
  // ZERO
  for (int i = 0; i <= segWidth; i++) {
    if (_value == 1) { // If 1 to 0, slide B to F and E to C

      // * // Move B right to left
      drawLine(segWidth - i, 1, segWidth - i, segHeight);
      if (i > 0)
        clrLine(segWidth + 1 - i, 1, segWidth + 1 - i, segHeight);

      // Move C right to left
      drawLine(segWidth - i, segHeight * 2 + 1, segWidth - i, segHeight + 2);
      if (i > 0)
        clrLine(segWidth + 1 - i, segHeight * 2 + 1, segWidth + 1 - i,
                segHeight + 2);

      if (i < segWidth)
        drawPixel(segWidth - i, 0); // Draw A
      if (i < segWidth)
        drawPixel(segWidth - i, segHeight * 2 + 2); // Draw D
    }

    if (_value == 2) { // If 2 to 0, slide B to F and Flow G to C
      drawLine(segWidth - i, 1, segWidth - i, segHeight);
      if (i > 0)
        clrLine(segWidth + 1 - i, 1, segWidth + 1 - i, segHeight);

      clrPixel(1 + i, segHeight + 1); // Erase G left to right
      if (i < segWidth)
        drawPixel(segWidth + 1, segHeight + 2 + i); // Draw C
    }

    if (_value == 3) { // B to F, C to E
      // slide B to F
      drawLine(segWidth - i, 1, segWidth - i, segHeight);
      if (i > 0)
        clrLine(segWidth + 1 - i, 1, segWidth + 1 - i, segHeight);

      // Move C to E
      drawLine(segWidth - i, segHeight * 2 + 1, segWidth - i, segHeight + 2);
      if (i > 0)
        clrLine(segWidth + 1 - i, segHeight * 2 + 1, segWidth + 1 - i,
                segHeight + 2);

      // Erase G from right to left
      clrPixel(segWidth - i, segHeight + 1); // G
    }

    if (_value == 5) { // If 5 to 0, we also need to slide F to B
      // // Move F left to right
      drawLine(1 + i, 1, 1 + i, segHeight);
      if (i > 0)
        clrLine(0 + i, 1, 0 + i, segHeight);
    }

    if (_value == 5 || _value == 9) { // If 9 or 5 to 0, Flow G into E
      if (i < segWidth) {
        drawPixel(0, segHeight + 2 + i);
        clrPixel(segWidth - i, segHeight + 1);
      }
    }
    usleep(transDelay);
    Matrix::draw();
    // delay(animSpeed);
  }
}

void Digit::Morph1() {
  // Zero or two to One
  for (int i = 0; i <= segWidth; i++) {
    // Move E left to right
    drawLine(1 + i, segHeight * 2 + 1, 1 + i, segHeight + 2);
    clrLine(i, segHeight * 2 + 1, i, segHeight + 2);

    // // Move F left to right
    drawLine(1 + i, 1, 1 + i, segHeight);
    clrLine(0 + i, 1, 0 + i, segHeight);

    // Gradually Erase A, G, D
    clrPixel(1 + i, 0);                 // A
    clrPixel(1 + i, segHeight * 2 + 2); // D
    clrPixel(1 + i, segHeight + 1);     // G

    // delay(animSpeed);
    usleep(transDelay);
    Matrix::draw();
  }
}

void Digit::Morph(uint8_t newValue) {
  switch (newValue) {
  case 2:
    Morph2();
    break;
  case 3:
    Morph3();
    break;
  case 4:
    Morph4();
    break;
  case 5:
    Morph5();
    break;
  case 6:
    Morph6();
    break;
  case 7:
    Morph7();
    break;
  case 8:
    Morph8();
    break;
  case 9:
    Morph9();
    break;
  case 0:
    Morph0();
    break;
  case 1:
    Morph1();
    break;
  }
  _value = newValue;
}
