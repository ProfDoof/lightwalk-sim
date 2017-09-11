class Led {
public:
  Led(int r, int g, int b, int brightness) {
    _r = r;
    _g = g;
    _b = b;
    _brightness = brightness;
  }
  int r() {return r;};
  int g() {return g;};
  int b() {return b;};
  int brightness() {return brightness;};

private:
  int _r;
  int _g;
  int _b;
  int _brightness;  
}
