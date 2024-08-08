#ifndef CPP4_3DVIEWER_V2_SRC_MODEL_AFFINETRANSFORMATION_H_
#define CPP4_3DVIEWER_V2_SRC_MODEL_AFFINETRANSFORMATION_H_

#include <cmath>
#include <cstddef>
#include <vector>

namespace s21 {

class matrix_t {
 private:
  std::vector<double> matrix;
  size_t rows;
  size_t cols;
  double prev_x = 0, prev_y = 0, prev_z = 0;
  double prev_zoom = 1;
  double prev_alpha = 0, prev_beta = 0, prev_gamma = 0;

 public:
  matrix_t() : rows(0), cols(0){};
  ~matrix_t() = default;

  void moveXYZ(double x, double y, double z);

  void rotationX(double alpha);
  void rotationY(double beta);
  void rotationZ(double gamma);
  void rotationXYZ(double alpha, double beta, double gamma);

  void zoom(double zoom);

  size_t getRows() const { return rows; }
  size_t getCols() const { return cols; }

  std::vector<double> getMatrix() { return matrix; }

  void setRows(size_t row) { rows = row; }
  void setCols(size_t col) { cols = col; }

  void insert(double x);
  double &operator()(size_t i, size_t j);

  void ClearMatrix();
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_SRC_MODEL_AFFINETRANSFORMATION_H_
