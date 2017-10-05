// TugOfWar.cpp
// An effect for ACU's Lightwalk
// Created by Cole Spears (cxs13b)

#include "interactiveEffect.h"
#include "application.h"

class GameManager {
public:
  GameManager(){}

  void startGame(long st){
    _teamOneColor = _rgbToColor(255, 0, 0);
    _teamTwoColor = _rgbToColor(0, 0, 255);
    _isGoing = true;
    startTime = st;

    //start colors (blue/red)
  }

  void endGame() {
    //winning color blinks to signify win
    //no colors for a little bit
    //can you return early from an effect?
    //end effect early or restart game?
    _isGoing = false;

  }

  bool _isGoing = false;

private:
  float _mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }

  uint32_t _rgbToColor(int r, int g, int b) {
    return (r << 16) + (g << 8) + b;
  }

  uint32_t _teamOneColor;
  uint32_t _teamTwoColor;
  long startTime;
};


class TugOfWar : public InteractiveEffect {
public:
  TugOfWar(int id, long startTime) : InteractiveEffect(id, startTime) {
    _startTime = startTime;

    if (!_gameManager._isGoing){
      // (why is the constructor being called multiple times? cout << "here" shows multiple times by end of program)
      
      // start the game
    }
  }

  bool cares(int x, int y) {
    //pretty much yeah, we care about all of them, except during gameOver scenerio
  }

  uint32_t colorFor(int x, int y) {
    //return _color;
  }

private:
  void _update() {
    //create some wobble?
  }

  void _movementOn(long currentTime, int xOffset, int nodeId) {
    //move percents, depending on team
  }

  void _movementOff(int xOffset, int nodeId) {
    //unsure what this means in this case... see WhackAMole?
  }

  GameManager _gameManager;
  long _startTime;
};