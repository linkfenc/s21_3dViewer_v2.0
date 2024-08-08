#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <math.h>

#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QTimer>

#include "../../controller/controller.h"
#include "colordata.h"

namespace s21 {

class GLWidget : public QOpenGLWidget {
  Q_OBJECT
 public:
  GLWidget(QWidget* parent = nullptr);

  enum class ProjectionMode { Central, Parallel };
  enum class LineMode { Solid, Stipple };
  enum class VertexMode { None, Dot, Square };

  // Setters
  void DataSet(s21::data& d);
  bool isEmptyData() { return data_ == nullptr; }
  void DataClear();
  void SetProjection(ProjectionMode mode) { projection_mode_ = mode; }
  void SetLineMode(LineMode mode) { line_mode_ = mode; }
  void SetVertexMode(VertexMode mode) { vertex_mode_ = mode; }
  void SetLineWidht(double w) { line_widht_ = w; }
  void SetVertexSize(double s) { vertex_size_ = s; }
  void SetBackGroundColor(ColorData color) { background_color_ = color; }
  void SetLineColor(ColorData color) { line_color_ = color; }
  void SetVertexColor(ColorData color) { vertex_color_ = color; }

  // Getters
  ProjectionMode GetProjMode() const { return projection_mode_; }
  LineMode GetLineMode() const { return line_mode_; }
  VertexMode GetVertexMode() const { return vertex_mode_; }
  double GetLineWidht() const { return line_widht_; }
  double GetVertexSize() const { return vertex_size_; }
  const ColorData GetBackgroundColor() const { return background_color_; }
  const ColorData GetLineColor() const { return line_color_; }
  const ColorData GetVertexColor() const { return vertex_color_; }

 private:
  double xRot = 0, yRot = 0, zRot = 0, line_widht_, vertex_size_ = 5;
  QPoint mPos;

  std::vector<int> f_arr;
  std::vector<double> v_arr;
  s21::data* data_ = nullptr;

  ProjectionMode projection_mode_ = ProjectionMode::Central;
  LineMode line_mode_ = LineMode::Solid;
  VertexMode vertex_mode_ = VertexMode::None;
  ColorData background_color_ =
      ColorData::CreateColorData(ColorData::Mode::cBackground);
  ColorData line_color_ = ColorData::CreateColorData(ColorData::Mode::cLine);
  ColorData vertex_color_ =
      ColorData::CreateColorData(ColorData::Mode::cVertex);

  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  void DrawObj();
  void glPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear,
                     GLdouble zFar);
  void ChoiceProjection();
  void ChoiceLineMode();
  void ChoiceVertexMode();

  void mousePressEvent(QMouseEvent*) override;
  void mouseMoveEvent(QMouseEvent*) override;
};

}  // namespace s21
#endif  // GLWIDGET_H
