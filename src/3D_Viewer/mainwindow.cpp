#include "mainwindow.h"

#include <stdio.h>

#include "glview.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowTitle("3D Viewer");

  ui->widget->load_settings_from_file();
  expose_condition_widget();

  timer_for_gif = new QTimer(0);  // parent must be null
  connect(timer_for_gif, SIGNAL(timeout()), this, SLOT(create_screen()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_open_file_clicked() {
  const char* filepath = NULL;
  QString str = QFileDialog::getOpenFileName(
      this, "Выбрать файл", "",
      "*.obj");  // , nullptr, QFileDialog::DontUseNativeDialog
  QByteArray file_path = str.toLocal8Bit();
  filepath = file_path.data();
  loading(ui->widget->data, (char*)filepath);

  matrixToArray(ui->widget->data);
  arrayofstructureToArray(ui->widget->data);
  ui->file_name->setText("File: " + str);
  ui->number_of_vertices->setText(
      "Number of vertices: " + QString::number(ui->widget->data->sum_vertexes));
  ui->number_of_edges->setText("Number of edges: " +
                               QString::number(ui->widget->data->sum_facets));
  ui->widget->update();
}

void MainWindow::on_execute_clicked() {
  ui->widget->xS = ui->scale_x->value();
  ui->widget->yS = ui->scale_y->value();
  ui->widget->zS = ui->scale_z->value();
  ui->widget->xMov = ui->move_x->value();
  ui->widget->yMov = ui->move_y->value();
  ui->widget->zMov = ui->move_z->value();
  ui->widget->xRot = ui->rotate_x->value();
  ui->widget->yRot = ui->rotate_y->value();
  ui->widget->zRot = ui->rotate_z->value();
  ui->widget->update();
}

void MainWindow::on_central_clicked() { ui->widget->frust = 1; }

void MainWindow::on_parallel_clicked() { ui->widget->frust = 0; }

void MainWindow::on_apply_clicked() {
  ui->widget->index_line = ui->type_edge->currentIndex();
  ui->widget->widthLine = ui->thickness->value();
  ui->widget->index_dot = ui->type_vertex->currentIndex();

  if (ui->type_vertex->currentIndex() == 0) {
    ui->widget->sizePoint = 0;
    ui->widget->index_dot = 0;
    std::cout << ui->type_vertex->currentIndex() << std::endl;
  } else {
    ui->widget->sizePoint = ui->size->value();
  }
  ui->widget->update();
}

void MainWindow::expose_condition_widget() {
  ui->scale_x->setValue(ui->widget->xS);
  ui->scale_y->setValue(ui->widget->yS);
  ui->scale_z->setValue(ui->widget->zS);

  ui->rotate_x->setValue(ui->widget->xRot);
  ui->rotate_y->setValue(ui->widget->yRot);
  ui->rotate_z->setValue(ui->widget->zRot);

  ui->move_x->setValue(ui->widget->xMov);
  ui->move_y->setValue(ui->widget->yMov);
  ui->move_z->setValue(ui->widget->zMov);

  if (ui->widget->frust == 1) {
    ui->central->setChecked(true);
  } else {
    ui->parallel->setChecked(true);
  }
  ui->type_edge->setCurrentIndex(ui->widget->index_line);
  ui->type_vertex->setCurrentIndex(ui->widget->index_dot);
  ui->thickness->setValue(ui->widget->widthLine);
  ui->size->setValue(ui->widget->sizePoint);
}

void MainWindow::on_save_clicked() {
  QString format;
  if (ui->format->currentIndex() == 0) {
    format = "*.jpeg";
  } else if (ui->format->currentIndex() == 1) {
    format = "*.bmp";
  }
  QString str =
      QFileDialog::getSaveFileName(0, "Сохранить файл как", "", format);
  ui->widget->grabFramebuffer().save(str);
}

void MainWindow::on_edge_color_clicked() {
  ui->widget->edge_color = QColorDialog::getColor(
      Qt::red, this, tr("colors"), QColorDialog::DontUseNativeDialog);
}

void MainWindow::on_background_color_clicked() {
  ui->widget->back_color = QColorDialog::getColor(
      Qt::red, this, tr("colors"), QColorDialog::DontUseNativeDialog);
}

void MainWindow::on_vertex_color_clicked() {
  ui->widget->vertex_color = QColorDialog::getColor(
      Qt::red, this, tr("colors"), QColorDialog::DontUseNativeDialog);
}

void MainWindow::on_record_gif_clicked() {
  if (flag_record == 0) {
    flag_record = 1;
    ui->record_gif->setStyleSheet(
        "QPushButton {color: red;  font: bold 14px;}");
    timer_for_gif->start(100);
    create_screen();
  }
}

void MainWindow::save_gif() {
  QString fileName = QFileDialog::getSaveFileName(
      this, tr("Save screenshot"), "",
      tr("GIF screenshot (*.gif);;GIF screenshot (*.gif)"));
  QGifImage gif(QSize(1800, 1700));

  gif.setDefaultTransparentColor(Qt::black);
  gif.setDefaultDelay(100);

  for (QVector<QImage>::Iterator img = mas_image.begin();
       img != mas_image.end(); ++img) {
    gif.addFrame(*img);
  }

  gif.save(fileName);
  mas_image.clear();
  time = 0.0;
  flag_record = 0;

  ui->record_gif->setStyleSheet(
      "QPushButton {color: Black;  font: bold 14px;}");
}

void MainWindow::create_screen() {
  if (flag_record == 1 && time <= 5.0) {
    mas_image.push_back(ui->widget->grab().toImage());
    time += 0.1;
  } else if (time >= 5.0) {
    save_gif();
    timer_for_gif->stop();
  }
}
