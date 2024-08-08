#ifndef MODEL_H
#define MODEL_H

#include "parser_file.h"

namespace s21 {

class Model {
 public:
  Model();
  ~Model();

  data &InitData(const std::string &filename);
  void Scale(double zoom);
  void Rotate(double x, double y, double z);
  void Move(double x, double y, double z);
  data getData() { return matrixs_v_f; }

 private:
  ParserFile *parser_file_;
  s21::data matrixs_v_f;
};

}  // namespace s21

#endif  // MODEL_H
