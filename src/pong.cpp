#include "pong.h"

float RandomFloat(float min, float max) {
  // this  function assumes max > min, you may want
  // more robust error checking for a non-debug build
  float random = ((float)rand()) / (float)RAND_MAX;
  // generate (in your case) a float between 0 and (4.5-.78)
  // then add .78, giving you a float between .78 and 4.5
  float range = max - min;
  return (random * range) + min;
}

Pong::Pong(configuration_t &config) : Matrix(config) {
  _paddleLeftY = 10;
  _paddleRigthY = 10;
  _ballVX = 1.3;
  _ballVY = BALLMINV;
  _ballX = _width / 2;
  _ballY = 10;
  _paddleLeftVy = 0.7;  //_ballVY + 0.1;
  _paddleRigthVy = 0.7; //_ballVY + 0.1;
  _playState = NORMAL;
  // callLeftTarget();
  callRigthTarget();
  pongTime.lt = time(NULL);
  pongTime.tm = localtime(&(pongTime.lt));
  pongTime.prevHour = pongTime.tm->tm_hour;
  pongTime.prevMin = pongTime.tm->tm_min;
  pongTime.hour[0] = pongTime.tm->tm_hour / 10;
  pongTime.hour[1] = pongTime.tm->tm_hour % 10;
  /* Set minutes */
  pongTime.minute[0] = pongTime.tm->tm_min / 10;
  pongTime.minute[1] = pongTime.tm->tm_min % 10;
}

void drawModern(int n, int x, int y){
  if (n>10)
    return;
  for(int j =0 ;j<FONTMH;j++){
    //for(int b=0;b<)
  }
}
void Pong::drawNumber(int n, int x, int y) {
    for (int j = 0; j < 5; j++) {
  for (int i = 0; i < 3; i++) {
      if (numberFont[n][i + 3 * j]) {
        setPix( i + x,j+y);
      }
    }
  }
}

void Pong::drawBigNumber(int n, int x, int y) {
  for (int j = 0; j < 5; j++) {
    for (int i = 0; i < 3; i++) {
      if (numberFont[n][i + 3 * j]) {
        setPix(i * 2 + x, j * 2 + y);
        setPix(i * 2 + x, j * 2 + y + 1);
        setPix(i * 2 + x + 1, j * 2 + y);
        setPix(i * 2 + x + 1, j * 2 + y + 1);
      }
    }
  }
}

void Pong::draw() {
  clearScreen();
  switch (_playState) {
  case NORMAL:
    if (_config.bigFont) {
      drawBigNumber(pongTime.hour[0], _width / 2 - 2 - 2 * FONTW * 2, 2);
      drawBigNumber(pongTime.hour[1], _width / 2 - 1 - FONTW * 2, 2);
      drawBigNumber(pongTime.minute[0], _width / 2 + 2, 2);
      drawBigNumber(pongTime.minute[1], _width / 2 + 3 + FONTW * 2, 2);
    } else {

      drawNumber(pongTime.hour[0], _width / 2 - 2 - 2 * FONTW, 2);
      drawNumber(pongTime.hour[1], _width / 2 - 1 - FONTW, 2);
      drawNumber(pongTime.minute[0], _width / 2 + 2, 2);
      drawNumber(pongTime.minute[1], _width / 2 + 3 + FONTW, 2);
    }
    break;
  case RIGTH_LOOSE:
  case LEFT_LOOSE:
    if (_config.bigFont) {
      drawBigNumber(pongTime.pHour[0], _width / 2 - 2 - 2 * FONTW * 2, 2);
      drawBigNumber(pongTime.pHour[1], _width / 2 - 1 - FONTW * 2, 2);
      drawBigNumber(pongTime.pMinute[0], _width / 2 + 1, 2);
      drawBigNumber(pongTime.pMinute[1], _width / 2 + 2 + FONTW * 2, 2);
    } else {
      drawNumber(pongTime.pHour[0], _width / 2 - 2 - 2 * FONTW, 2);
      drawNumber(pongTime.pHour[1], _width / 2 - 1 - FONTW, 2);
      drawNumber(pongTime.pMinute[0], _width / 2 + 1, 2);
      drawNumber(pongTime.pMinute[1], _width / 2 + 2 + FONTW, 2);
    }
    break;
  }
  // Draw the middle line
  for (int i = 0; i < _heigth; i += 2) {
    setPix( _width / 2,i);
  }
  // Draw the padels
  for (int i = 0; i < PADTHICK; i++) {
    for (int j = 0; j < PADHEIGTH; j++) {
      setPix(i,j + _paddleLeftY);
      setPix( i + _width - PADTHICK,_paddleRigthY + j);
    }
  }
  // Draw the ball

  for (int i = 0; i < BALLSIZE; i++) {
    for (int j = 0; j < BALLSIZE; j++) {
      setPix( _ballX + j,_ballY + i);
    }
  }

  Matrix::draw();
  // move(0, 0);
  // printw("Ytarg %f", _paddleLeftYTarget);
  // move(1, 0);
  // printw("Yf: %f Yd: %d ", _paddleLeftY, (int)_paddleLeftY);
  // move(2, 0);
  // printw("Yball %f", _ballY);
}

void Pong::updateTime() {
  pongTime.lt = time(NULL);
  pongTime.tm = localtime(&(pongTime.lt));

  if (pongTime.prevMin != pongTime.tm->tm_min) {
    if (_ballVX < 0) {
      _playState = LEFT_LOOSE;
      callLeftTarget();
    } else {
      _playState = RIGTH_LOOSE;
      callRigthTarget();
    }
    pongTime.pHour[0] = pongTime.prevHour / 10;
    pongTime.pHour[1] = pongTime.prevHour % 10;
    /* Set minutes */
    pongTime.pMinute[0] = pongTime.prevMin / 10;
    pongTime.pMinute[1] = pongTime.prevMin % 10;

    pongTime.prevMin = pongTime.tm->tm_min;
    pongTime.prevHour = pongTime.tm->tm_hour;
    /* Set minutes */
    pongTime.hour[0] = pongTime.tm->tm_hour / 10;
    pongTime.hour[1] = pongTime.tm->tm_hour % 10;
    /* Set minutes */
    pongTime.minute[0] = pongTime.tm->tm_min / 10;
    pongTime.minute[1] = pongTime.tm->tm_min % 10;
  }
}

void Pong::update() {
  updateTime();
  updateBall();
  updatePaddles();
}

// Calculates where the verticle position where the ball will hit
void Pong::callRigthTarget() {
  // Call where the ball will hit
  float startX = _ballX;
  float startY = _ballY;
  float ballVy = _ballVY;
  float ballVx = _ballVX;
  int ticks = 0; // Number of ticks to reach target

  while (startX <= _width - PADTHICK) {
    ticks++;
    startX += _ballVX;
    startY += ballVy;
    if (startY >= _heigth - BALLSIZE) {
      startY = _heigth - BALLSIZE;
      ballVy = -ballVy;
    } else if (startY <= 0) {
      ballVy = -ballVy;
      startY = 0;
    }
  }
  switch (_playState) {
  case NORMAL:
    _paddleRigthYTarget = startY - PADHEIGTH / 2;
    break;
  case RIGTH_LOOSE:
    if (startY <= _heigth / 2)
      _paddleRigthYTarget = startY + 4;
    else
      _paddleRigthYTarget = startY - 3 - PADHEIGTH;
    break;
  }
  float minSpeed = abs(_paddleRigthY - _paddleRigthYTarget) / ticks;
  _paddleRigthVy = RandomFloat(minSpeed, minSpeed * 1.3); // add some randomness
}

void Pong::callLeftTarget() {
  // Call where the ball will hit
  float startX = _ballX;
  float startY = _ballY;
  float ballVy = _ballVY;
  int ticks = 0; // Number of ticks to reach target
  while (startX >= PADTHICK) {
    ticks++;
    startX += _ballVX;
    startY += ballVy;
    if (startY >= _heigth - BALLSIZE) {
      startY = _heigth - BALLSIZE;
      ballVy = -ballVy;
    } else if (startY <= 0) {
      ballVy = -ballVy;
      startY = 0;
    }
  }

  switch (_playState) {
  case NORMAL:
    _paddleLeftYTarget = startY - PADHEIGTH / 2;
    break;
  case LEFT_LOOSE:
    if (startY <= _heigth / 2)
      _paddleLeftYTarget = startY + 4;
    else
      _paddleLeftYTarget = startY - 3 - PADHEIGTH;
    break;
  }
  // Call the minimum speed of paddle to reach target;
  float minSpeed = abs(_paddleLeftYTarget - _paddleLeftY) / ticks;
  _paddleLeftVy = RandomFloat(minSpeed, minSpeed * 1.3); // add some randomness
}

void Pong::updateBall() {
  _ballX += _ballVX;
  _ballY += _ballVY;
  if (_ballY >= _heigth - BALLSIZE) {
    _ballY = _heigth - BALLSIZE;
    _ballVY = -_ballVY;
  } else if (_ballY <= 0) {
    _ballVY = -_ballVY;
    _ballY = 0;
  }
  if (_playState == NORMAL) {
    if (_ballX > _width - PADTHICK - 3) {
      // add some randomsse to y component affter bounce
      if (_ballVY < 0)
        _ballVY = RandomFloat(-BALLMAXV, -BALLMINV);
      else
        _ballVY = RandomFloat(BALLMINV, BALLMAXV);
      _ballVX = -_ballVX;
      _ballX = _width - PADTHICK - BALLSIZE;
      _paddleRigthYTarget = RandomFloat(0, _heigth - PADHEIGTH);
      _paddleRigthVy = RandomFloat(0.5, 1.5);
      callLeftTarget();
    } else if (_ballX <= 0 + PADTHICK) {
      if (_ballVY < 0)
        _ballVY = RandomFloat(-BALLMAXV, -BALLMINV);
      else
        _ballVY = RandomFloat(BALLMINV, BALLMAXV);
      _ballVX = -_ballVX;
      _ballX = PADTHICK;
      _paddleLeftYTarget = RandomFloat(0, _heigth - PADHEIGTH);
      _paddleLeftVy = RandomFloat(0.5, 1.5);
      callRigthTarget();
    }
  }

  if (_playState == RIGTH_LOOSE) {
    if (_ballX > _width) {
      _playState = NORMAL;
      _ballVX = 1;
      _ballVY = 1.3;
      _ballX = _width / 2;
      _ballY = 10;
      callRigthTarget();
      return;
    }
  }

  if (_playState == LEFT_LOOSE) {
    if (_ballX < -BALLSIZE) {
      _playState = NORMAL;
      _ballVX = 1;
      _ballVY = 1.3;
      _ballX = _width / 2;
      _ballY = 10;
      callRigthTarget();
      return;
    }
  }
}

void Pong::updatePaddles() {

  if (_paddleLeftY - _paddleLeftVy > _paddleLeftYTarget)
    _paddleLeftY -= _paddleLeftVy;
  else if (_paddleLeftY < _paddleLeftYTarget)
    _paddleLeftY += _paddleLeftVy;

  if (_paddleLeftY >= _heigth - PADHEIGTH) {
    _paddleLeftY = _heigth - PADHEIGTH;
  }
  if (_paddleLeftY < 0) {
    _paddleLeftY = 0;
  }

  if (_paddleRigthY - _paddleRigthVy > _paddleRigthYTarget)
    _paddleRigthY -= _paddleRigthVy;
  else if (_paddleRigthY < _paddleRigthYTarget)
    _paddleRigthY += _paddleRigthVy;

  if (_paddleRigthY >= _heigth - PADHEIGTH) {
    _paddleRigthY = _heigth - PADHEIGTH;
  }
  if (_paddleRigthY < 0) {
    _paddleRigthY = 0;
  }
  // _paddleLeftY = floor(_paddleLeftY);
  // _paddleRigthY = floor(_paddleRigthY);
}
