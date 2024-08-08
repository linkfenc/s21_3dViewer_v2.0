#ifndef COLORDATA_H
#define COLORDATA_H

namespace s21 {

class ColorData {
 public:
  enum class Mode { cUnknown, cBackground, cLine, cVertex };
  static ColorData CreateColorData(Mode mode = Mode::cUnknown) {
    ColorData color_data(mode);
    switch (mode) {
      case Mode::cUnknown:
        color_data.SetColor(0, 0, 0, 1);
        break;
      case Mode::cBackground:
        color_data.SetColor(0, 0, 0, 1);
        break;
      default:
        color_data.SetColor(255, 0, 0, 1);
        break;
    }
    return color_data;
  }

  void SetColor(double r, double g, double b, double a) {
    red_ = r;
    green_ = g;
    blue_ = b;
    alpha_ = a;
  }

  double GetRed() const { return red_; }
  double GetGreen() const { return green_; }
  double GetBlue() const { return blue_; }
  double GetAlha() const { return alpha_; }

 private:
  Mode mode_;
  double red_, green_, blue_, alpha_;
  ColorData(Mode mode = Mode::cUnknown) : mode_(mode) {}
};

}  // namespace s21

#endif  // COLORDATA_H
