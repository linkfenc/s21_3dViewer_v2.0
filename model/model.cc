#include "model.h"

namespace s21 {

Model::Model() : parser_file_(new ParserFile) {}

Model::~Model() { delete parser_file_; }

data& Model::InitData(const std::string& filename) {
  parser_file_->parseFile(filename, matrixs_v_f);
  return matrixs_v_f;
}

void Model::Scale(double zoom) { matrixs_v_f.matrix_3d.zoom(zoom); }

void Model::Rotate(double x, double y, double z) {
  matrixs_v_f.matrix_3d.rotationXYZ(x, y, z);
}

void Model::Move(double x, double y, double z) {
  matrixs_v_f.matrix_3d.moveXYZ(x, y, z);
}

}  // namespace s21
