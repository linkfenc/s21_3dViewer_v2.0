#ifndef CPP4_3DVIEWER_V2_SRC_MODEL_STRUCTS_H_
#define CPP4_3DVIEWER_V2_SRC_MODEL_STRUCTS_H_

#include "matrix_t.h"

namespace s21 {

class data {
 public:
  size_t count_of_vertexes;
  size_t count_of_facets;
  s21::matrix_t matrix_3d;
  std::vector<int> polygons;
  data() : count_of_vertexes(0), count_of_facets(0) {}
  double max_d = 0;

  void ClearData() {
    count_of_facets = 0;
    count_of_vertexes = 0;
    polygons.clear();
    max_d = 0;
    matrix_3d.ClearMatrix();
  }
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_SRC_MODEL_STRUCTS_H_
