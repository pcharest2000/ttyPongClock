#ifndef __PONG_H_
#define __PONG_H_
#include "matrix.h"
#include <time.h>
#define PADTHICK 2
#define PADHEIGTH 12
#define BALLMAXV 0.9
#define BALLMINV 0.3
#define BALLSIZE 2
#define FONTW 3
#define FONTH 5
#define FONTMW 15
#define FONTMH 32
#define FONTMWBYTE 2

/* Number matrix */
const bool numberFont[][15] = {
    {1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1}, /* 0 */
    {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1}, /* 1 */
    {1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1}, /* 2 */
    {1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1}, /* 3 */
    {1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1}, /* 4 */
    {1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1}, /* 5 */
    {1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1}, /* 6 */
    {1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1}, /* 7 */
    {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1}, /* 8 */
    {1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1}, /* 9 */
};
enum playState_t { NORMAL, LEFT_LOOSE, RIGTH_LOOSE };
typedef struct {
  unsigned int hour[2];
  unsigned int minute[2];
  unsigned int pHour[2];
  unsigned int pMinute[2];
  int prevHour;
  int prevMin;
  /* time.h utils */
  struct tm *tm;
  time_t lt;
} pongTime_t;

class Pong : public Matrix {

public:
  Pong(configuration_t &config);
  void update();
  void draw();

private:
  float _paddleLeftY;
  float _paddleRigthY;
  float _paddleLeftYTarget;
  float _paddleRigthYTarget;
  float _paddleLeftVy;
  float _paddleRigthVy;
  float _ballX;
  float _ballY;
  float _ballVY;
  float _ballVX;
  pongTime_t pongTime;
  playState_t _playState;
  void updateBall();
  void updatePaddles();
  void drawNumber(int n, int x, int y);
  void drawBigNumber(int n, int x, int y);
  void callLeftTarget();
  void callRigthTarget();
  void updateTime();
  void drawModern(int x, int y);
};
#endif // __PONG_H_
