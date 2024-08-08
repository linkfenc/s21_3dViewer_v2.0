#include <cmath>

#include "../model/model.cc"
#include "gtest/gtest.h"

TEST(InitTest, Test1) {
  s21::Model model_;
  s21::data data_;
  data_ = model_.InitData("obj/test.obj");
  EXPECT_EQ(data_.count_of_facets, 3);
  EXPECT_EQ(data_.count_of_vertexes, 3);
  EXPECT_EQ(data_.max_d, 9);
  EXPECT_EQ(data_.polygons.size(), 18);
  EXPECT_EQ(data_.matrix_3d.getMatrix().size(), 9);
  EXPECT_EQ(data_.polygons.front(), 0);
  EXPECT_EQ(data_.polygons.back(), 6);
  EXPECT_EQ(data_.matrix_3d.getMatrix().front(), 1 / data_.max_d);
  EXPECT_EQ(data_.matrix_3d.getMatrix().back(), 9 / data_.max_d);
  EXPECT_EQ(data_.matrix_3d.getRows(), 3);
  EXPECT_EQ(data_.matrix_3d.getCols(), 3);
}

TEST(ClearTest, Test2) {
  s21::Model model_;
  s21::data data_;
  data_ = model_.InitData("obj/test.obj");
  data_.ClearData();
  EXPECT_EQ(data_.count_of_facets, 0);
  EXPECT_EQ(data_.count_of_vertexes, 0);
  EXPECT_EQ(data_.max_d, 0);
  EXPECT_EQ(data_.matrix_3d.getMatrix().size(), 0);
  EXPECT_EQ(data_.polygons.size(), 0);
  EXPECT_EQ(data_.matrix_3d.getRows(), 0);
  EXPECT_EQ(data_.matrix_3d.getCols(), 0);
}

TEST(RotateTest, Test3) {
  s21::Model model_;
  s21::data data_;
  data_ = model_.InitData("obj/test.obj");
  model_.Rotate(90, 90, 90);
  EXPECT_EQ(model_.getData().count_of_facets, 3);
  EXPECT_EQ(model_.getData().count_of_vertexes, 3);
  EXPECT_EQ(model_.getData().max_d, 9);
  EXPECT_EQ(model_.getData().polygons.size(), 18);
  EXPECT_EQ(model_.getData().matrix_3d.getMatrix().size(), 9);
  EXPECT_EQ(model_.getData().polygons.front(), 0);
  EXPECT_EQ(model_.getData().polygons.back(), 6);
  EXPECT_NEAR(model_.getData().matrix_3d.getMatrix().front(), 1.0 / 9, 1e-7);
  EXPECT_NEAR(model_.getData().matrix_3d.getMatrix().back(), 1.0 / 3, 1e-7);
  EXPECT_EQ(model_.getData().matrix_3d.getRows(), 3);
  EXPECT_EQ(model_.getData().matrix_3d.getCols(), 3);
}

TEST(RotateTest, Test3_5) {
  s21::Model model_;
  s21::data data_;
  data_ = model_.InitData("obj/test.obj");
  model_.Rotate(90, 90, 90);
  model_.Rotate(0, 0, 0);
  EXPECT_EQ(data_.count_of_facets, 3);
  EXPECT_EQ(data_.count_of_vertexes, 3);
  EXPECT_EQ(data_.max_d, 9);
  EXPECT_EQ(data_.polygons.size(), 18);
  EXPECT_EQ(data_.matrix_3d.getMatrix().size(), 9);
  EXPECT_EQ(data_.polygons.front(), 0);
  EXPECT_EQ(data_.polygons.back(), 6);
  EXPECT_EQ(data_.matrix_3d.getMatrix().front(), 1 / data_.max_d);
  EXPECT_EQ(data_.matrix_3d.getMatrix().back(), 9 / data_.max_d);
  EXPECT_EQ(data_.matrix_3d.getRows(), 3);
  EXPECT_EQ(data_.matrix_3d.getCols(), 3);
}

TEST(MoveTest, Test4) {
  s21::Model model_;
  s21::data data_;
  data_ = model_.InitData("obj/test.obj");
  model_.Move(5, -5, 4);
  EXPECT_EQ(model_.getData().count_of_facets, 3);
  EXPECT_EQ(model_.getData().count_of_vertexes, 3);
  EXPECT_EQ(model_.getData().max_d, 9);
  EXPECT_EQ(model_.getData().polygons.size(), 18);
  EXPECT_EQ(model_.getData().matrix_3d.getMatrix().size(), 9);
  EXPECT_EQ(model_.getData().polygons.front(), 0);
  EXPECT_EQ(model_.getData().polygons.back(), 6);
  EXPECT_NEAR(model_.getData().matrix_3d.getMatrix().front(),
              1 / model_.getData().max_d + 5, 1e-7);
  EXPECT_NEAR(model_.getData().matrix_3d(1, 1), 5 / model_.getData().max_d - 5,
              1e-7);
  EXPECT_NEAR(model_.getData().matrix_3d.getMatrix().back(),
              9 / model_.getData().max_d + 4, 1e-7);
  EXPECT_EQ(model_.getData().matrix_3d.getRows(), 3);
  EXPECT_EQ(model_.getData().matrix_3d.getCols(), 3);
}

TEST(ScaleTest, Test5) {
  s21::Model model_;
  s21::data data_;
  data_ = model_.InitData("obj/test.obj");
  model_.Scale(2);
  EXPECT_EQ(model_.getData().count_of_facets, 3);
  EXPECT_EQ(model_.getData().count_of_vertexes, 3);
  EXPECT_EQ(model_.getData().max_d, 9);
  EXPECT_EQ(model_.getData().polygons.size(), 18);
  EXPECT_EQ(model_.getData().matrix_3d.getMatrix().size(), 9);
  EXPECT_EQ(model_.getData().polygons.front(), 0);
  EXPECT_EQ(model_.getData().polygons.back(), 6);
  EXPECT_NEAR(model_.getData().matrix_3d.getMatrix().front(),
              1 / model_.getData().max_d * 2, 1e-7);
  EXPECT_NEAR(model_.getData().matrix_3d(1, 1), 5 / model_.getData().max_d * 2,
              1e-7);
  EXPECT_NEAR(model_.getData().matrix_3d.getMatrix().back(),
              9 / model_.getData().max_d * 2, 1e-7);
  EXPECT_EQ(model_.getData().matrix_3d.getRows(), 3);
  EXPECT_EQ(model_.getData().matrix_3d.getCols(), 3);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
