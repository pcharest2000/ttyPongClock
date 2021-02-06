#include "config.h"
#include "matrix.h"
#include "pong.h"
#include <getopt.h>
int main(int argc, char **argv) {
configuration_t config = {.fgColor = 7, .bgColor = 0, .frameRate = 20};
  int c;
  while ((c = getopt(argc, argv, "hC:B:F:")) != -1) {
    switch (c) {
    case 'h':
    default:
      printf(
          "usage : tty-pong clock [-iuvsScbtrahDBxn] [-C [0-7]] [-f format] "
          "[-d "
          "delay] [-a nsdelay] [-T tty] \n"
          "    -C            Set color                                      \n"
          "    -B            Set background color                           \n"
          "    -F            Set frame rate def 20                          "
          "\n");
      exit(EXIT_SUCCESS);
      break;
    case 'C':
      if (atoi(optarg) >= 0 && atoi(optarg) < 8)
        config.fgColor = atoi(optarg);
      break;
    case 'B':
      if (atoi(optarg) >= 0 && atoi(optarg) < 8)
        config.bgColor = atoi(optarg);
      break;
    case 'F':
      if (atoi(optarg) >= 1 && atoi(optarg) < 70)
        config.frameRate = atoi(optarg);
      break;
    }
  }
  //
  // nodelay(stdscr, TRUE);
  // Matrix mat = Matrix();
  Pong pong = Pong(config);
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
