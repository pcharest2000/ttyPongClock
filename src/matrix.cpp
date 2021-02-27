#include "matrix.h"

vector<vector<int>> Matrix::mat;
int Matrix::_width;
int Matrix::_heigth;
configuration_t Matrix::_config;

Matrix::Matrix(configuration_t &config) {
  time_t t;
  srand((unsigned)time(&t));
  if (stdscr == NULL) {
    _config = config;
    printf("hello");
    setlocale(LC_ALL, "");
    initscr();
    if (has_colors() == FALSE) {
      printf("Terminal has no color exitng\n");
      exit(EXIT_FAILURE);
    }
    // cbreak();
    keypad(stdscr, TRUE); /* We get F1, F2 etc..		*/
    curs_set(0);
    timeout(1000 / config.frameRate); // 30fps
    /*
    * If you set a custom background, curses changes it to black
    * This makes it optional.
    */
    if (config.useColor) {
      start_color();
      init_pair(1, config.fgColor, config.bgColor);
    }
    
    attron(COLOR_PAIR(1));
    getmaxyx(stdscr, _heigth, _width);
    _heigth = _heigth * 2;
    // Alocate the pixel array
    mat.resize(_heigth);
    for (int j = 0; j < _heigth; j++)
      mat[j].resize(_width);
  }
}

void Matrix::draw() {
  for (int j = 0; j < _heigth - 1; j += 2) {
    for (int i = 0; i < _width; i++) {
      move(j / 2, i);
      if (mat[j][i] == 1 && mat[j + 1][i] == 1)
        printw("█");
      else if (mat[j][i] == 1 && mat[j + 1][i] == 0)
        printw("▀");
      else if (mat[j][i] == 0 && mat[j + 1][i] == 1)
        printw("▄");
      else
        printw(" ");
    }
  }
  //setPix2(2, 0);
  refresh();
}

void Matrix::clearScreen() {
  for (int j = 0; j < _heigth; j++)
    for (int i = 0; i < _width; i++)
      mat[j][i] = 0;
}

void Matrix::setPix2(int x, int y) {
  chtype in = mvinch(y / 2, x);

  int filtered = in & A_CHARTEXT;
  move(10, 10);
  addch(filtered);
  // if (filtered=='▀'){
  // printw("A");
  // }
  // else

  // printw("B");
  // printw("A");
  // printf("%c",'A');
  // putc(filtered,stdout);
  // printf("%c",filtered);
  // move(y / 2, x);

  // if (mat[j][i] == 1 && mat[j + 1][i] == 1)
  // printw("█");
  // else if (mat[j][i] == 1 && mat[j + 1][i] == 0)
  //   printw("▀");
  // else if (mat[j][i] == 0 && mat[j + 1][i] == 1)
  //   printw("▄");
  // else
  //   printw(" ");
  // if (y >= _heigth || x >= _width || x < 0 || y < 0)
  //   return;
  // mat[y][x] = 1;
}

void Matrix::setPix(int x, int y) {
  if (y >= _heigth || x >= _width || x < 0 || y < 0)
    return;
  mat[y][x] = 1;
}

void Matrix::clrPix(int x, int y) {
  if (y >= _heigth || x >= _width || x < 0 || y < 0)
    return;
  mat[y][x] = 0;
}
void Matrix::resize() {
  getmaxyx(stdscr, _heigth, _width);
  _heigth = _heigth * 2;
  // Alocate the pixel array
  Matrix::mat.resize(_heigth);
  for (int j = 0; j < _heigth; j++)
    mat[j].resize(_width);
}

void Matrix::clrLine(int x0, int y0, int x1, int y1) {
  int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = (dx > dy ? dx : -dy) / 2, e2;

  for (;;) {
    clrPix(x0, y0);
    if (x0 == x1 && y0 == y1)
      break;
    e2 = err;
    if (e2 > -dx) {
      err -= dy;
      x0 += sx;
    }
    if (e2 < dy) {
      err += dx;
      y0 += sy;
    }
  }
}
void Matrix::drawLine(int x0, int y0, int x1, int y1) {
  int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = (dx > dy ? dx : -dy) / 2, e2;

  for (;;) {
    setPix(x0, y0);
    if (x0 == x1 && y0 == y1)
      break;
    e2 = err;
    if (e2 > -dx) {
      err -= dy;
      x0 += sx;
    }
    if (e2 < dy) {
      err += dx;
      y0 += sy;
    }
  }
}

void Matrix::drawFillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
  for (uint j = 0; j < h; j++)
    for (uint i = 0; i < w; i++)
      setPix(i + x, j + y);
}
