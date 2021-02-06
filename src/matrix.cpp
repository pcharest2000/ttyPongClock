#include "matrix.h"

Matrix::Matrix(configuration_t &config) {
  setlocale(LC_ALL, "");
  time_t t;
  srand((unsigned)time(&t));
  initscr();
  if (has_colors() == FALSE) {
    printf("Terminal has no color exitng\n");
    exit(EXIT_FAILURE);
  }
  cbreak();
  keypad(stdscr, TRUE); /* We get F1, F2 etc..		*/
  //  noecho();
  curs_set(0);
  timeout(1000 / config.frameRate); // 30fps
  start_color();
  init_pair(1, config.fgColor, config.bgColor);
  attron(COLOR_PAIR(1));
  // timeout(1000);//30fps
  getmaxyx(stdscr, heigth, width);
  heigth = heigth * 2;
  // Alocate the pixel array
  mat.resize(heigth);
  for (int i = 0; i < heigth; i++)
    mat[i].resize(width);
}

void Matrix::draw() {
  for (int i = 0; i < heigth - 1; i += 2) {
    for (int j = 0; j < width; j++) {
      move(i / 2, j);
      if (mat[i][j] == 1 && mat[i + 1][j] == 1)
        printw("█");
      else if (mat[i][j] == 1 && mat[i + 1][j] == 0)
        printw("▀");
      else if (mat[i][j] == 0 && mat[i + 1][j] == 1)
        printw("▄");
      else
        printw(" ");
    }
  }
}

void Matrix::clearScreen() {
  for (int i = 0; i < heigth; i++)
    for (int j = 0; j < width; j++)
      mat[i][j] = 0;
}

void Matrix::set(int i, int j) {
  if (i >= heigth || j >= width)
    return;
  mat[i][j] = 1;
}

void Matrix::clr(int i, int j) {
  if (i >= heigth || j >= width)
    return;
  mat[i][j] = 0;
}
void Matrix::fillRnd() {

  for (int i = 0; i < heigth; i++)
    for (int j = 0; j < width; j++)
      mat[i][j] = rand() % 2;
}
void Matrix::resize() {
  getmaxyx(stdscr, heigth, width);
  heigth = heigth * 2;
  // Alocate the pixel array
  mat.resize(heigth);
  for (int i = 0; i < heigth; i++)
    mat[i].resize(width);
}
