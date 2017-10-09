#include <ctime>
#include <chrono>

class Gradient {
public:
  Gradient() {}

  void configure(int r1, int g1, int b1, int r2, int g2, int b2) {
    _r1 = r1; _g1 = g1; _b1 = b1;
    _r2 = r2; _g2 = g2; _b2 = b2;

    _dR = abs(r1 - r2);
    _dG = abs(g1 - g2);
    _dB = abs(b1 - b2);

    if (_rgbToColorGrad(_r1, _g1, _b1) > _rgbToColorGrad(_r2, _g2, _b2)){ //inverse delta colors if c1 > c2
      _dR = _dR * -1;
      _dG = _dG * -1;
      _dB = _dB * -1;
    }
  }

  uint32_t calculateColor(float localPercentage) {
    if (localPercentage == 0)
      return _rgbToColorGrad(_r1, _g1, _b1);
    return _rgbToColorGrad(_r1 + (_dR * localPercentage), _g1 + (_dG * localPercentage), _b1 + (_dB * localPercentage));
  }

  uint32_t _rgbToColorGrad(int r, int g, int b) {
    return (r << 16) + (g << 8) + b;
  }

private:
  int count = 1;
  int _r1, _g1, _b1;
  int _r2, _g2, _b2;
  int _dR, _dG, _dB;
};