#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>

#include "../../model/model.h"

namespace s21 {

class Controller {
 public:
  Controller();
  ~Controller();

  data &InitDate(const std::string &filename);
  void Scale(double zoom);
  void Rotate(double x, double y, double z);
  void Move(double x, double y, double z);

 private:
  Model *model_;
};
}  // namespace s21
#endif  // CONTROLLER_H
