#ifndef __CONFIG_H_
#define __CONFIG_H_

typedef struct {
  int fgColor;
  int bgColor;
  int frameRate;
  bool bigFont;
  bool useColor;
} configuration_t;
// configuration_t config = {.fgColor = 0, .bgColor = 7, .frameRate = 20};
// extern configuration_t config;
#endif // __CONFIG_H_
