#include "main.h"
#include "matrix.h"
#include "pong.h"
int main() {
  // nodelay(stdscr, TRUE);
  //Matrix mat = Matrix();
  Pong pong = Pong();
  int c;
  while (1) {
    pong.update();
    pong.draw();
    // mat.draw();
    refresh();
    c = getch();
    switch (c) {
    case KEY_RESIZE:
     pong.resize();
      break;
    case 'q':
      endwin();
      return 0;
      break;
    }
  }
}
