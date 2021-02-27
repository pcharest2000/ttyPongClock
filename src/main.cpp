/* license {{{ */
/*

tty-pong-clock

A nice animated pong clock that runs in the terminal..
Author, current maintainer: Philippe Charest <philippe.charest@gmail.com>

Copyright (C) 2021

This program is free software which I release under the GNU General Public
License. You may redistribute and/or modify this program under the terms
of that license as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

To get a copy of the GNU General Puplic License,  write to the
Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/
/* }}} */
#include "config.h"
#include "digit.h"
#include "matrix.h"
#include "pong.h"
#include <getopt.h>
int main(int argc, char **argv) {

  configuration_t config = {
      .fgColor = 7, .bgColor = 0, .frameRate = 20, .bigFont = FALSE};
  int c;
  while ((c = getopt(argc, argv, "hbcC:B:F:")) != -1) {
    switch (c) {
    case 'h':
    default:
      printf(
          "usage : tty-pong-clock [-b] [-c] [-B [0-7] -C [0-7] -F [1-60] ]          "
          "  \n"
          "    -c            Enable curses setting back/foreground colors   \n"
          "    -C            Set forground color (implies -c)               \n"
          "    -B            Set background color (implies -c)              \n"
          "    -F            Set frame rate default 30 fps                  \n"
          "    -b            Set big font                                     "
          "\n");
      exit(EXIT_SUCCESS);
      break;
    case 'C':
      if (atoi(optarg) >= 0 && atoi(optarg) < 8) {
        config.useColor = TRUE;
        config.fgColor = atoi(optarg);
      }
      break;
    case 'B':
      if (atoi(optarg) >= 0 && atoi(optarg) < 8) {
        config.useColor = TRUE;
        config.bgColor = atoi(optarg);
      }
      break;
    case 'F':
      if (atoi(optarg) >= 1 && atoi(optarg) <= 60)
        config.frameRate = atoi(optarg);
      break;
    case 'b':
      config.bigFont = TRUE;
      break;
    case 'c':
      config.useColor = TRUE;
      break;
    }
  }
   Pong pong = Pong(config);
  // Digit hour2 = Digit(config, 0, 20, 2);
  // Digit hour = Digit(config, 0, 0, 0);
  uint8_t i = 0;
   // hour.Draw(i);
   // hour2.Draw(i);
  while (1) {
    i++;
    if (i > 9)
      i = 0;


     // hour2.Morph(i);
     // hour.Morph(i);
    pong.update();
    pong.draw();
    c = getch();
    switch (c) {
    case KEY_RESIZE:
      // hour.resize();
       pong.resize();
      break;
    case 'Q':
    case 'q':
      endwin();
      return 0;
      break;
    }
  //  hour.draw();
  }
}
