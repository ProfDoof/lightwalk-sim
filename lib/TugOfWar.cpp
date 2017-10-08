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
    teamWinner = 0; //No winner yet

    blinkCount = 0; //reset values for win condition
    countThreshold = 300;
    maxThreshold = 1500;
  }

  void endGame() {
    _isGoing = false;
  }

  uint32_t getWinnerColor(){
    if (teamWinner == 1)
      return _teamOneColor;
    return _teamTwoColor;
  }

  bool _isGoing = false;
  float _teamOnePercent;
  uint32_t _teamOneColor = _gmRGBToColor(0, 0, 255);
  uint32_t _teamTwoColor = _gmRGBToColor(255, 0, 0);
  int teamWinner;
  int blinkCount;
  int countThreshold;
  int maxThreshold;

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
    else {
      if (_gameManager.blinkCount > _gameManager.countThreshold/2){  //if count is divisble by 500
        return true;
      }
    }
    return false;
  }

  uint32_t colorFor(int x, int y) {
    float localPercent = ((x + _xOffset) * 1.0) / (NODE_COUNT * REED_COUNT);
    if (_gameManager._isGoing){
      if (localPercent < _gameManager._teamOnePercent) 
        return _gameManager._teamOneColor;
      return _gameManager._teamTwoColor;
    }
    else {
      return _gameManager.getWinnerColor();
    }
 }

private:
  void _update() {
    //check end game case
    if (_gameManager._teamOnePercent <= .05){ //least xOffset value percent
      _gameManager._isGoing = false;
      _gameManager.teamWinner = 1;
    }
    else if (_gameManager._teamOnePercent > .95){ //greatest xOffset value perecent
      _gameManager._isGoing = false;
      _gameManager.teamWinner = 2;
    }

    if (_gameManager.teamWinner){ //if someone has won

      if (_gameManager.blinkCount > _gameManager.countThreshold)
        _gameManager.blinkCount = 0;

      _gameManager.blinkCount++;
      _gameManager.maxThreshold--;

      if (_gameManager.maxThreshold == 0){
        _gameManager.startGame(_startTime);
      }
    }
  }

  void _movementOn(long currentTime, int xOffset, int nodeId) {
    float localPercent = ((xOffset + diff/2) * 1.0) / (NODE_COUNT * REED_COUNT);

    // move perecent based upon realtime percents (teams have to move to fit their color)
    if (localPercent < _gameManager._teamOnePercent)  //(localPercent <= .5) if want to split half-way
      _gameManager._teamOnePercent = _gameManager._teamOnePercent - .025;
    else
      _gameManager._teamOnePercent = _gameManager._teamOnePercent + .025;

    // must "reset" _activeMovements back to 0. _movementOn returns if _activeMovements == NODE_COUNT
    _activeMovements -= 1;
  }

  void _movementOff(int xOffset, int nodeId) {
  }

  GameManager _gameManager;
  int diff = 12;
  long _startTime;
};