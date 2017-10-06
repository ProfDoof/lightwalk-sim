// TugOfWar.cpp
// An effect for ACU's Lightwalk
// Created by Cole Spears (cxs13b)

//Ideas:
    //colors blink to signify starting?
    //winning color blinks to signify win
    //restart game?

#include "interactiveEffect.h"
#include "application.h"

class GameManager {
public:
  GameManager(){}

  void startGame(long st){
    _teamOnePercent = .5;
    _isGoing = true;
    startTime = st;
  }

  void endGame() {
    _isGoing = false;
  }

  bool _isGoing = false;
  float _teamOnePercent;
  uint32_t _teamOneColor = _gmRGBToColor(0, 0, 255);
  uint32_t _teamTwoColor = _gmRGBToColor(255, 0, 0);

private:
  uint32_t _gmRGBToColor(int r, int g, int b) {
    return (r << 16) + (g << 8) + b;
  }

  long startTime;
};


class TugOfWar : public InteractiveEffect {
public:
  TugOfWar(int id, long startTime) : InteractiveEffect(id, startTime) {
    _startTime = startTime;

    if (!_gameManager._isGoing)
      _gameManager.startGame(_startTime);
  }

  bool cares(int x, int y) {
    if (_gameManager._isGoing)
      return true;
    return false;
  }

  uint32_t colorFor(int x, int y) {
    float localPercent = ((x + _xOffset) * 1.0) / (NODE_COUNT * REED_COUNT);

    if (localPercent < _gameManager._teamOnePercent) 
      return _gameManager._teamOneColor;
    return _gameManager._teamTwoColor;
 }

private:
  void _update() {
    //check end game case
    if (_gameManager._teamOnePercent <= .05){ //least xOffset value percent
      _gameManager._isGoing = false; //teamOne wins
    }
    else if (_gameManager._teamOnePercent > .95){ //greatest xOffset value perecent
      _gameManager._isGoing = false; //teamTwo wins
    }
  }

  void _movementOn(long currentTime, int xOffset, int nodeId) {
    float localPercent = (xOffset * 1.0) / (NODE_COUNT * REED_COUNT);

      // move perecent based upon realtime percents (teams have to move to fit their color)
    if (localPercent < _gameManager._teamOnePercent)
      _gameManager._teamOnePercent = _gameManager._teamOnePercent - .025;
    else
      _gameManager._teamOnePercent = _gameManager._teamOnePercent + .025;

    // must "reset" _activeMovements back to 0. _movementOn returns is _activeMovements = NODE_COUNT"
    _activeMovements -= 1;

    //  move percent based upon half-way point (teams do not have to move fit their color)
    // if (localPercent <= .5){
    //   _gameManager._teamOnePercent = _gameManager._teamOnePercent - .025;
    //   cout << "Here 1" << endl;
    // }
    // else {
    //   _gameManager._teamOnePercent = _gameManager._teamOnePercent + .025;
    //   cout << "Here 2" << endl;
    // }
  }

  void _movementOff(int xOffset, int nodeId) {
    //unsure what this means in this case... see WhackAMole?
  }

  GameManager _gameManager;
  long _startTime;
};