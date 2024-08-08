#include "glwidget.h"

s21::GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget(parent) {}

void s21::GLWidget::DataSet(s21::data& d) {
  data_ = &d;
  update();
}

void s21::GLWidget::DataClear() {
  if (data_) data_->ClearData();
}

void s21::GLWidget::initializeGL() {
  setlocale(LC_ALL, "C");
  glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
  glEnable(GL_DEPTH_TEST);
}

void s21::GLWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void s21::GLWidget::paintGL() {
  glClearColor(background_color_.GetRed(), background_color_.GetGreen(),
               background_color_.GetBlue(), background_color_.GetAlha());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  ChoiceProjection();

  glLineWidth(line_widht_);
  ChoiceLineMode();
  glColor4f(line_color_.GetRed(), line_color_.GetGreen(), line_color_.GetBlue(),
            line_color_.GetAlha());

  glRotatef(xRot, 1, 0, 0);
  glRotatef(yRot, 0, 1, 0);

  DrawObj();

  glColor4f(vertex_color_.GetRed(), vertex_color_.GetGreen(),
            vertex_color_.GetBlue(), vertex_color_.GetAlha());

  glPointSize(vertex_size_);
  if (data_ != nullptr) ChoiceVertexMode();
  glDisableClientState(GL_VERTEX_ARRAY);
}

void s21::GLWidget::DrawObj() {
  if (data_ != nullptr) {
    v_arr = data_->matrix_3d.getMatrix();
    glVertexPointer(3, GL_DOUBLE, 0, v_arr.data());
  }
  glEnableClientState(GL_VERTEX_ARRAY);
  if (data_ != nullptr) {
    f_arr = data_->polygons;
    glDrawElements(GL_LINES, f_arr.size(), GL_UNSIGNED_INT, f_arr.data());
  }
  //  glDisableClientState(GL_VERTEX_ARRAY);
}

void s21::GLWidget::glPerspective(GLdouble fovy, GLdouble aspect,
                                  GLdouble zNear, GLdouble zFar) {
  GLdouble xMin, yMin, xMax, yMax;
  yMax = zNear * tan(fovy * M_PI / 360);
  yMin = -yMax;
  xMin = yMin * aspect;
  xMax = yMax * aspect;
  glFrustum(xMin, xMax, yMin, yMax, zNear, zFar);
}

void s21::GLWidget::ChoiceProjection() {
  if (projection_mode_ == ProjectionMode::Central) {
    glOrtho(-1, 1, -1, 1, -1000, 1000);
  } else {
    glPerspective(120.0f, (float)(width() / height()), 0.1f, 1000.0f);
    //    GLdouble aspect = (GLdouble)width()/(GLdouble)height();
    //    glFrustum(-aspect, aspect,  -1, 1,  0.01f, 1000.0f);
  }
}

void s21::GLWidget::ChoiceLineMode() {
  if (line_mode_ == LineMode::Solid) {
    if (glIsEnabled(GL_LINE_STIPPLE)) glDisable(GL_LINE_STIPPLE);
  } else {
    if (!glIsEnabled(GL_LINE_STIPPLE)) glEnable(GL_LINE_STIPPLE);
    glLineStipple(3, 15);
  }
}

void s21::GLWidget::ChoiceVertexMode() {
  if (vertex_mode_ == VertexMode::Dot) {
    if (!glIsEnabled(GL_POINT_SMOOTH)) glEnable(GL_POINT_SMOOTH);
    glDrawArrays(GL_POINTS, 0, data_->count_of_vertexes);
  } else if (vertex_mode_ == VertexMode::Square) {
    if (glIsEnabled(GL_POINT_SMOOTH)) glDisable(GL_POINT_SMOOTH);
    glDrawArrays(GL_POINTS, 0, data_->count_of_vertexes);
  }
}

void s21::GLWidget::mousePressEvent(QMouseEvent* mo) { mPos = mo->pos(); }

void s21::GLWidget::mouseMoveEvent(QMouseEvent* mo) {
  xRot = 1 / M_PI * (mo->pos().y() - mPos.y());
  yRot = 1 / M_PI * (mo->pos().x() - mPos.x());
  update();
}
