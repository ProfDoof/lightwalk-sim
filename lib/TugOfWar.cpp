// TugOfWar.cpp
// An effect for ACU's Lightwalk
// Created by Cole Spears (cxs13b)

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
    //winning color blinks to signify win
    //no colors for a little bit
    //can you return early from an effect?
    //end effect early or restart game?
    _isGoing = false;
  }

  bool _isGoing = false;
  float _teamOnePercent;
  //float teamTwoPercent; // = remaining percent
  uint32_t _teamOneColor = _gmRGBToColor(0, 0, 255);
  uint32_t _teamTwoColor = _gmRGBToColor(255, 0, 0);

private:
  float _mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }

  uint32_t _gmRGBToColor(int r, int g, int b) {
    return (r << 16) + (g << 8) + b;
  }

  long startTime;
};


class TugOfWar : public InteractiveEffect {
public:
  TugOfWar(int id, long startTime) : InteractiveEffect(id, startTime) {
    _startTime = startTime;

    if (!_gameManager._isGoing){
      // (why is the constructor being called multiple times? cout << "here" shows multiple times by end of program)
      _gameManager.startGame(_startTime);
    }
  }

  bool cares(int x, int y) {
    //pretty much yeah, we care about all of them, except during gameOver scenerio
    if (_gameManager._isGoing)
      return true;
    return false;
  }

  uint32_t colorFor(int x, int y) {
    float localPercent = ((x + _xOffset) * 1.0) / (SIM_NODES * 10); //MAX_WIDTH;

    if (localPercent < _gameManager._teamOnePercent) 
      return _gameManager._teamOneColor;
    return _gameManager._teamTwoColor;
 }

private:
  void _update() {
    //Will be updating percents in _movementOn
    //create some wobble?
  }

  void _movementOn(long currentTime, int xOffset, int nodeId) {
    //move percents, depending on team
    //how to calculate percent with xOffset?
    cout << "Movement on: " << xOffset << endl;
  }

  void _movementOff(int xOffset, int nodeId) {
    //unsure what this means in this case... see WhackAMole?
  }

  GameManager _gameManager;
  long _startTime;
};