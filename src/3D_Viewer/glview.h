#ifndef GLVIEW_H
#define GLVIEW_H

#define GL_SILENCE_DEPRECATION

#include <QColorDialog>
#include <QSettings>
#include <QWheelEvent>
#include <QtOpenGL>
#include <QtOpenGLWidgets>
#include <QtWidgets/QWidget>

#include "mainwindow.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "../Back.h"
#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class glView;
}
QT_END_NAMESPACE

class glView : public QOpenGLWidget {
  Q_OBJECT

 private:
  QPoint mPos;
  QTimer tmr;
  void drawCube(double d);
  void drawObject();
  void mousePressEvent(QMouseEvent *);
  void mouseMoveEvent(QMouseEvent *);
  void wheelEvent(QWheelEvent *);
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();

 public:
  glView(QWidget *parent = nullptr);
  ~glView();
  int v = 0;
  t_universe a;
  t_universe *data = &a;
  int frust = 1;
  double xS = 1;
  double yS = 1;
  double zS = 1;
  double xMov = 0;
  double yMov = 0;
  double zMov = -10;
  double xRot, yRot, zRot;
  int widthLine = 1;
  int index_line = 0;
  int index_dot = 0;
  int sizePoint = 0;

  QColor edge_color = QColor(255, 255, 255);
  QColor back_color = QColor(255, 0, 255);
  QColor vertex_color;

  void record_settings_to_file();
  void load_settings_from_file();

  QSettings *settings;

 private:
  Ui::glView *ui;
};
#endif  // GLVIEW_H
