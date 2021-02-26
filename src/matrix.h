#ifndef __MATRIX_H_
#define __MATRIX_H_

#include "config.h"
#include <ctype.h>
#include <locale.h>
#include <math.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <vector>
using namespace std;
class Matrix {
protected:
  static int _width;
  static int _heigth;
  static configuration_t _config;
  static vector<vector<int>> mat;

public:
  Matrix(configuration_t &config);
  void draw();
  void clearScreen();
  void setPix2(int x, int y);
  void setPix(int i, int j);
  void clrPix(int i, int j);
  void drawLine(int x0, int y0, int x1, int y1);
  void clrLine(int i, int j, int i2, int j2);
  void drawFillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
  void fillRnd();
  void resize();
};
#endif // __MATRIX_H_
