#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// #include <QOpenGLWidget>
// #include <QGridLayout>
// #include <QWidget>
#include <QFileDialog>
#include <QTimer>
#include <QVector>
#include <iostream>

#include "QtGifImage-master/src/gifimage/qgifimage.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "../Back.h"
#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  QVector<QImage> mas_image;

 private slots:
  void on_open_file_clicked();
  void on_execute_clicked();
  void on_central_clicked();
  void on_parallel_clicked();
  void on_apply_clicked();
  void expose_condition_widget();
  void on_save_clicked();
  void on_edge_color_clicked();
  void on_background_color_clicked();
  void on_vertex_color_clicked();

  void on_record_gif_clicked();
  void save_gif();
  void create_screen();

 private:
  Ui::MainWindow *ui;
  int flag_record = 0;
  QTimer *timer_for_gif;
  double time = 0;
};
#endif  // MAINWINDOW_H
