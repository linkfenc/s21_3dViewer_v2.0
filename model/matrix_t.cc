#include "matrix_t.h"

#include <iostream>

double &s21::matrix_t::operator()(size_t i, size_t j) {
  return matrix[i * cols + j];
}

void s21::matrix_t::ClearMatrix() {
  rows = 0;
  cols = 0;
  matrix.clear();
}

void s21::matrix_t::insert(double x) { matrix.push_back(x); }

void s21::matrix_t::moveXYZ(double x, double y, double z) {
  double prev_move = prev_zoom;
  zoom(1);
  for (size_t i = 0; i != rows; ++i) {
    matrix[i * cols] += x - prev_x;
    matrix[i * cols + 1] += y - prev_y;
    matrix[i * cols + 2] += z - prev_z;
  }
  prev_x = x;
  prev_y = y;
  prev_z = z;
  zoom(prev_move);
}

void s21::matrix_t::zoom(double zoom) {
  for (size_t i = 0; i != rows; ++i) {
    for (size_t j = 0; j != cols; ++j) {
      matrix[i * cols + j] *= zoom / prev_zoom;
    }
  }
  prev_zoom = zoom;
}

void s21::matrix_t::rotationX(double alpha) {
  double y, z;
  for (size_t i = 0; i < matrix.size(); i += 3) {
    y = matrix[i + 1];
    z = matrix[i + 2];
    matrix[i + 1] = y * cos(alpha) - z * sin(alpha);
    matrix[i + 2] = y * sin(alpha) + z * cos(alpha);
  }
}

void s21::matrix_t::rotationY(double beta) {
  double x, z;
  for (size_t i = 0; i < matrix.size(); i += 3) {
    x = matrix[i];
    z = matrix[i + 2];
    matrix[i] = x * cos(beta) + z * sin(beta);
    matrix[i + 2] = -x * sin(beta) + z * cos(beta);
  }
}

void s21::matrix_t::rotationZ(double gamma) {
  double x, y;
  for (size_t i = 0; i < matrix.size(); i += 3) {
    x = matrix[i];
    y = matrix[i + 1];
    matrix[i] = x * cos(gamma) - y * sin(gamma);
    matrix[i + 1] = x * sin(gamma) + y * cos(gamma);
  }
}

void s21::matrix_t::rotationXYZ(double alpha, double beta, double gamma) {
  double unrotate = 0;
  if (prev_alpha != 0) {
    unrotate = prev_alpha;
    prev_alpha = 0;
    rotationXYZ(-unrotate * 180 / M_PI, 0, 0);
  } else if (prev_beta != 0) {
    unrotate = prev_beta;
    prev_beta = 0;
    rotationXYZ(0, -unrotate * 180 / M_PI, 0);
  } else if (prev_gamma != 0) {
    unrotate = prev_gamma;
    prev_gamma = 0;
    rotationXYZ(0, 0, -unrotate * 180 / M_PI);
  }
  alpha = alpha * M_PI / 180;
  beta = beta * M_PI / 180;
  gamma = gamma * M_PI / 180;
  double centerX = 0, centerY = 0, centerZ = 0;
  for (size_t i = 0; i < matrix.size(); i += 3) {
    centerX += matrix[i];
    centerY += matrix[i + 1];
    centerZ += matrix[i + 2];
  }
  centerX /= rows;
  centerY /= rows;
  centerZ /= rows;
  for (size_t i = 0; i < matrix.size(); i += 3) {
    matrix[i] -= centerX;
    matrix[i + 1] -= centerY;
    matrix[i + 2] -= centerZ;
  }
  rotationX(alpha);
  rotationY(beta);
  rotationZ(gamma);
  prev_alpha = alpha;
  prev_beta = beta;
  prev_gamma = gamma;
  for (size_t i = 0; i < matrix.size(); i += 3) {
    matrix[i] += centerX;
    matrix[i + 1] += centerY;
    matrix[i + 2] += centerZ;
  }
}
