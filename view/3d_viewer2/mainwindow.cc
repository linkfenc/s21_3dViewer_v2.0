#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(s21::Controller* c, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), controller_(c) {
  ui->setupUi(this);
  LoadSettings();
  connect(&timer_giff_, SIGNAL(timeout()), this, SLOT(MakeGiff()));
}

MainWindow::~MainWindow() {
  SaveSettings();
  delete ui;
}

void MainWindow::on_pushButton_openFile_clicked() {
  QString file_name_ = QFileDialog::getOpenFileName(
      this, tr("Open File"), QDir::currentPath(), tr("Object (*.obj)"));
  if (file_name_ != "") {
    ui->OGLWidget->DataClear();
    ResetMoveAndRotate();
    s21::data& data_ = controller_->InitDate(file_name_.toStdString());
    ui->OGLWidget->DataSet(data_);
    ui->fileName->setText(file_name_);
    ui->qEdges->setText(QString::number(data_.count_of_facets));
    ui->qVertices->setText(QString::number(data_.count_of_vertexes));
  }
  //  GLWidget::DataSet(DATA_);
}

void MainWindow::on_pushButton_BGColor_clicked() {
  s21::ColorData color = ui->OGLWidget->GetBackgroundColor();
  ChangeColor(color);
  ui->OGLWidget->SetBackGroundColor(color);
  ui->OGLWidget->update();
}

void MainWindow::on_pushButton_Edges_color_clicked() {
  s21::ColorData color = ui->OGLWidget->GetLineColor();
  ChangeColor(color);
  ui->OGLWidget->SetLineColor(color);
  ui->OGLWidget->update();
}

void MainWindow::on_pushButton_Vertex_color_clicked() {
  s21::ColorData color = ui->OGLWidget->GetVertexColor();
  ChangeColor(color);
  ui->OGLWidget->SetVertexColor(color);
  ui->OGLWidget->update();
}

void MainWindow::ChangeColor(s21::ColorData& color) {
  double r, g, b, a;
  QColor tmp;
  tmp.setRgbF(color.GetRed(), color.GetGreen(), color.GetBlue(),
              color.GetAlha());
  QColor color_dialog = QColorDialog::getColor(tmp);
  if (color_dialog.isValid()) {
    color_dialog.getRgbF(&r, &g, &b, &a);
    color.SetColor(r, g, b, a);
  }
}

void MainWindow::SaveSettings() {
  settings_.setValue("LineWidht", ui->OGLWidget->GetLineWidht());
  settings_.setValue("VertexSize", ui->OGLWidget->GetVertexSize());
  settings_.setValue("ProjMode",
                     static_cast<int>(ui->OGLWidget->GetProjMode()));
  settings_.setValue("LineMode",
                     static_cast<int>(ui->OGLWidget->GetLineMode()));
  settings_.setValue("VertexMode",
                     static_cast<int>(ui->OGLWidget->GetVertexMode()));

  s21::ColorData color = ui->OGLWidget->GetLineColor();
  settings_.setValue("LineColorR", color.GetRed());
  settings_.setValue("LineColorG", color.GetGreen());
  settings_.setValue("LineColorB", color.GetBlue());
  settings_.setValue("LineColorA", color.GetAlha());

  color = ui->OGLWidget->GetVertexColor();
  settings_.setValue("VertexColorR", color.GetRed());
  settings_.setValue("VertexColorG", color.GetGreen());
  settings_.setValue("VertexColorB", color.GetBlue());
  settings_.setValue("VertexColorA", color.GetAlha());

  color = ui->OGLWidget->GetBackgroundColor();
  settings_.setValue("BackColorR", color.GetRed());
  settings_.setValue("BackColorG", color.GetGreen());
  settings_.setValue("BackColorB", color.GetBlue());
  settings_.setValue("BackColorA", color.GetAlha());
}

void MainWindow::LoadSettings() {
  ui->OGLWidget->SetLineWidht(settings_.value("LineWidht").toDouble());
  ui->lineWidth->setValue(ui->OGLWidget->GetLineWidht());
  ui->OGLWidget->SetVertexSize(settings_.value("VertexSize").toDouble());
  ui->vertexSize->setValue(ui->OGLWidget->GetVertexSize());
  ui->OGLWidget->SetProjection(
      s21::GLWidget::ProjectionMode(settings_.value("ProjMode").toInt()));
  if (ui->OGLWidget->GetProjMode() == s21::GLWidget::ProjectionMode::Central)
    ui->centralB->toggle();
  else
    ui->parallelB->toggle();
  ui->OGLWidget->SetLineMode(
      s21::GLWidget::LineMode(settings_.value("LineMode").toInt()));
  if (ui->OGLWidget->GetLineMode() == s21::GLWidget::LineMode::Solid) {
    ui->solidEdgesB->toggle();
  } else {
    ui->dashedEdgesB->toggle();
  }

  ui->OGLWidget->SetVertexMode(
      s21::GLWidget::VertexMode(settings_.value("VertexMode").toInt()));
  if (ui->OGLWidget->GetVertexMode() == s21::GLWidget::VertexMode::Dot) {
    ui->dotModeR->toggle();
  } else if (ui->OGLWidget->GetVertexMode() ==
             s21::GLWidget::VertexMode::Square) {
    ui->squarModeR->toggle();
  } else {
    ui->noneModeR->toggle();
  }

  s21::ColorData color =
      s21::ColorData::CreateColorData(s21::ColorData::Mode::cLine);
  color.SetColor(settings_.value("LineColorR").toDouble(),
                 settings_.value("LineColorG").toDouble(),
                 settings_.value("LineColorB").toDouble(),
                 settings_.value("LineColorA").toDouble());
  ui->OGLWidget->SetLineColor(color);
  color = s21::ColorData::CreateColorData(s21::ColorData::Mode::cVertex);
  color.SetColor(settings_.value("VertexColorR").toDouble(),
                 settings_.value("VertexColorG").toDouble(),
                 settings_.value("VertexColorB").toDouble(),
                 settings_.value("VertexColorA").toDouble());
  ui->OGLWidget->SetVertexColor(color);
  color = s21::ColorData::CreateColorData(s21::ColorData::Mode::cBackground);
  color.SetColor(settings_.value("BackColorR").toDouble(),
                 settings_.value("BackColorG").toDouble(),
                 settings_.value("BackColorB").toDouble(),
                 settings_.value("BackColorA").toDouble());
  ui->OGLWidget->SetBackGroundColor(color);
  ui->OGLWidget->update();
}

void MainWindow::ResetMoveAndRotate() {
  ui->Rx->setValue(0);
  ui->Ry->setValue(0);
  ui->Rz->setValue(0);
  ui->Mx->setValue(0);
  ui->My->setValue(0);
  ui->Mz->setValue(0);
}

void MainWindow::on_scale_value_valueChanged(double value) {
  if (!ui->OGLWidget->isEmptyData()) controller_->Scale(value);
  ui->OGLWidget->update();
}

void MainWindow::on_Rx_valueChanged(double Rx) {
  if (!ui->OGLWidget->isEmptyData())
    controller_->Rotate(Rx, ui->Ry->value(), ui->Rz->value());
  ui->OGLWidget->update();
}

void MainWindow::on_Ry_valueChanged(double Ry) {
  if (!ui->OGLWidget->isEmptyData())
    controller_->Rotate(ui->Rx->value(), Ry, ui->Rz->value());
  ui->OGLWidget->update();
}

void MainWindow::on_Rz_valueChanged(double Rz) {
  if (!ui->OGLWidget->isEmptyData())
    controller_->Rotate(ui->Rx->value(), ui->Ry->value(), Rz);
  ui->OGLWidget->update();
}

void MainWindow::on_Mx_valueChanged(double Mx) {
  if (!ui->OGLWidget->isEmptyData())
    controller_->Move(Mx, ui->My->value(), ui->Mz->value());
  ui->OGLWidget->update();
}

void MainWindow::on_My_valueChanged(double My) {
  if (!ui->OGLWidget->isEmptyData())
    controller_->Move(ui->Mx->value(), My, ui->Mz->value());
  ui->OGLWidget->update();
}

void MainWindow::on_Mz_valueChanged(double Mz) {
  if (!ui->OGLWidget->isEmptyData())
    controller_->Move(ui->Mx->value(), ui->My->value(), Mz);
  ui->OGLWidget->update();
}

void MainWindow::on_parallelB_clicked(bool checked) {
  if (checked) {
    ui->OGLWidget->SetProjection(s21::GLWidget::ProjectionMode::Parallel);
    ui->OGLWidget->update();
  }
}

void MainWindow::on_centralB_clicked(bool checked) {
  if (checked) {
    ui->OGLWidget->SetProjection(s21::GLWidget::ProjectionMode::Central);
    ui->OGLWidget->update();
  }
}

void MainWindow::on_solidEdgesB_clicked(bool checked) {
  if (checked) {
    ui->OGLWidget->SetLineMode(s21::GLWidget::LineMode::Solid);
    ui->OGLWidget->update();
  }
}

void MainWindow::on_dashedEdgesB_clicked(bool checked) {
  if (checked) {
    ui->OGLWidget->SetLineMode(s21::GLWidget::LineMode::Stipple);
    ui->OGLWidget->update();
  }
}

void MainWindow::on_lineWidth_valueChanged(double value) {
  ui->OGLWidget->SetLineWidht(value);
  ui->OGLWidget->update();
}

void MainWindow::on_vertexSize_valueChanged(double value) {
  ui->OGLWidget->SetVertexSize(value);
  ui->OGLWidget->update();
}

void MainWindow::on_noneModeR_clicked(bool checked) {
  if (checked) {
    ui->OGLWidget->SetVertexMode(s21::GLWidget::VertexMode::None);
    ui->OGLWidget->update();
  }
}

void MainWindow::on_dotModeR_clicked(bool checked) {
  if (checked) {
    ui->OGLWidget->SetVertexMode(s21::GLWidget::VertexMode::Dot);
    ui->OGLWidget->update();
  }
}

void MainWindow::on_squarModeR_clicked(bool checked) {
  if (checked) {
    ui->OGLWidget->SetVertexMode(s21::GLWidget::VertexMode::Square);
    ui->OGLWidget->update();
  }
}

void MainWindow::on_screenshotB_clicked() {
  QFileDialog connectImage(this);
  QString imageName = connectImage.getSaveFileName(
      this, tr("Make screenshot"), "../../*.jpeg", tr("image (*.bmp, *.jpeg)"));
  if (imageName != "") {
    QImage img = ui->OGLWidget->grabFramebuffer();
    img.save(imageName);
    QMessageBox messBoxImg;
    messBoxImg.information(0, "s21", "Screenshotsaved");
  }
}

void MainWindow::on_giffB_clicked() {
  giff_file_name_ = QFileDialog::getSaveFileName(
      this, tr("Make Giff"), "../../*.giff", tr("giff (*.giff)"));
  if (giff_file_name_ != "") {
    ui->giffB->setDisabled(true);
    giff_img_ = new QGifImage;
    giff_img_->setDefaultDelay(10);
    timer_giff_.setInterval(100);
    timer_giff_.start();
  }
}

void MainWindow::MakeGiff() {
  QImage img = ui->OGLWidget->grabFramebuffer();
  QSize imgSize(640, 800);
  QImage imgScaled = img.scaled(imgSize);
  giff_img_->addFrame(imgScaled);
  if (fps_ > 50) {
    timer_giff_.stop();
    giff_img_->save(giff_file_name_);
    fps_ = 0;
    QMessageBox GiffFinishMess;
    GiffFinishMess.information(0, "s21", "Giff Saved");
    delete giff_img_;
    giff_img_ = nullptr;
    ui->giffB->setEnabled(true);
    ui->giffB->setText("Giff");
  }
  fps_++;
  if (!ui->giffB->isEnabled()) {
    ui->giffB->setText(QString::number(fps_ / 10));
  }
}
