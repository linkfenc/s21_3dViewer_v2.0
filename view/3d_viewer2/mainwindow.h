#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QTimer>

#include "../../QtgifImage/qgifimage.h"
#include "glwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(s21::Controller *c = nullptr, QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pushButton_openFile_clicked();
  void on_pushButton_BGColor_clicked();

  void on_pushButton_Edges_color_clicked();

  void on_pushButton_Vertex_color_clicked();

  void on_scale_value_valueChanged(double value);

  void on_Rx_valueChanged(double Rx);
  void on_Ry_valueChanged(double Ry);
  void on_Rz_valueChanged(double Rz);

  void on_Mx_valueChanged(double Mx);
  void on_My_valueChanged(double My);
  void on_Mz_valueChanged(double Mz);

  void on_parallelB_clicked(bool checked);
  void on_centralB_clicked(bool checked);

  void on_solidEdgesB_clicked(bool checked);
  void on_dashedEdgesB_clicked(bool checked);

  void on_lineWidth_valueChanged(double value);
  void on_vertexSize_valueChanged(double value);

  void on_noneModeR_clicked(bool checked);
  void on_dotModeR_clicked(bool checked);
  void on_squarModeR_clicked(bool checked);

  void on_screenshotB_clicked();
  void on_giffB_clicked();
  void MakeGiff();

 private:
  Ui::MainWindow *ui;
  s21::Controller *controller_;
  QSettings settings_;

  void ChangeColor(s21::ColorData &color);
  void SaveSettings();
  void LoadSettings();
  void ResetMoveAndRotate();

  QString giff_file_name_;
  QTimer timer_giff_;
  QGifImage *giff_img_;
  int fps_;
};
#endif  // MAINWINDOW_H
