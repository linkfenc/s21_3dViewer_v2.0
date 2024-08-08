#include "controller.h"

namespace s21 {

Controller::Controller() : model_(new Model) {}

Controller::~Controller() { delete model_; }

data& Controller::InitDate(const std::string& filename) {
  return model_->InitData(filename);
}

void Controller::Scale(double zoom) { model_->Scale(zoom); }

void Controller::Rotate(double x, double y, double z) {
  model_->Rotate(x, y, z);
}

void Controller::Move(double x, double y, double z) { model_->Move(x, y, z); }

}  // namespace s21
