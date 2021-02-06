#ifndef __MATRIX_H_
#define __MATRIX_H_

#include <ctype.h>
#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <vector>
#include <math.h>
#include "config.h"
using namespace std;
class Matrix {
protected:
  int width;
  int heigth;
  vector<vector<int>> mat;

public:
  Matrix(configuration_t &config);
  void draw();
  void clearScreen();
  void set(int i, int j);
  void clr(int i, int j);
  void fillRnd();
  void resize();

};

#endif // __MATRIX_H_
