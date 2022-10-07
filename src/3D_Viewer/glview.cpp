#include "glview.h"

#include "ui_mainwindow.h"

glView::glView(QWidget* parent) : QOpenGLWidget(parent) {
  setWindowTitle("3D Viewer");
  setGeometry(400, 200, 800, 600);

  data->array_3d = NULL;
  data->indexes_array = NULL;
  data->v = 0;
  data->min = 0;
  data->max = 0;
  data->sum_vertexes = 0;
  data->sum_facets = 0;
  data->polygons = NULL;

  settings = new QSettings(
      QCoreApplication::applicationDirPath() + "/settings_demo.conf",
      QSettings::IniFormat);
}

glView::~glView() {}

void glView::initializeGL() { glEnable(GL_DEPTH_TEST); }

void glView::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void glView::paintGL() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (frust == 1) {
    glFrustum(data->min, data->max, data->min, data->max, data->max,
              data->max * 3);
  } else {
    glOrtho(data->min, data->max, data->min, data->max, data->min, data->max);
  }
  glClearColor(back_color.red() / 255.0, back_color.green() / 255.0,
               back_color.blue() / 255.0, 0);  // Цвет фона
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glScaled(xS, yS, zS);
  if (frust == 1) {
    glTranslated(xMov, yMov, zMov - (data->max - data->min));
  } else {
    glTranslated(xMov, yMov, zMov);
  }
  glRotated(xRot, 1, 0, 0);
  glRotated(yRot, 0, 1, 0);
  glRotated(zRot, 0, 0, 1);
  drawObject();
  update();
}

void glView::mousePressEvent(QMouseEvent* mo) { mPos = mo->pos(); }

void glView::mouseMoveEvent(QMouseEvent* mo) {
  xRot = 1 / M_PI * (mo->pos().y() - mPos.y());
  yRot = 1 / M_PI * (mo->pos().x() - mPos.x());
  update();
}

void glView::wheelEvent(QWheelEvent* event) {
  if (event->angleDelta().y() > 0) {
    xS *= 0.9;
    yS *= 0.9;
    zS *= 0.9;
  } else {
    xS *= 1.1;
    yS *= 1.1;
    zS *= 1.1;
  }
  update();
}

void glView::drawObject() {
  glColor3d(vertex_color.red() / 255.0, vertex_color.green() / 255.0,
            vertex_color.blue() / 255.0);  // Цвет вершины
  if (index_dot == 1) {
    glDisable(GL_POINT_SMOOTH);
    glPointSize(sizePoint);
  } else if (index_dot == 2) {
    glEnable(GL_POINT_SMOOTH);
    glPointSize(sizePoint);
  }
  glVertexPointer(3, GL_DOUBLE, 0, data->array_3d);
  glEnableClientState(GL_VERTEX_ARRAY);
  if (index_dot != 0) {
    glDrawArrays(GL_POINTS, 1, data->sum_vertexes);
  }
  glColor3d(edge_color.red() / 255.0, edge_color.green() / 255.0,
            edge_color.blue() / 255.0);  // Цвет линий
  glLineWidth(widthLine);
  glLineStipple(2, 0X00FF);  // Устанавливаем режим рисования линий
  if (index_line == 1) {
    glEnable(GL_LINE_STIPPLE);  // Открываем режим рисования линий (пунктир)
  }
  glDrawElements(GL_LINES, data->v * 2, GL_UNSIGNED_INT, data->indexes_array);

  glDisable(GL_LINE_STIPPLE);  // Отключить режим рисования линии (сплошная)
  glDisable(GL_POINT_SMOOTH);
  glDisableClientState(GL_VERTEX_ARRAY);

  record_settings_to_file();
}

void glView::record_settings_to_file() {
  settings->beginGroup("Widgets_settings");

  settings->setValue("edge_color", edge_color);
  settings->setValue("back_color", back_color);
  settings->setValue("vertex_color", vertex_color);

  settings->setValue("xS", xS);
  settings->setValue("yS", yS);
  settings->setValue("zS", zS);

  settings->setValue("xRot", xRot);
  settings->setValue("yRot", yRot);
  settings->setValue("zRot", zRot);

  settings->setValue("xMov", xMov);
  settings->setValue("yMov", yMov);
  settings->setValue("zMov", zMov);

  settings->setValue("frust", frust);

  settings->setValue("index_line", index_line);
  settings->setValue("index_dot", index_dot);
  settings->setValue("widthLine", widthLine);
  settings->setValue("sizePoint", sizePoint);

  settings->endGroup();
}

void glView::load_settings_from_file() {
  settings->beginGroup("Widgets_settings");

  edge_color = settings->value("edge_color", edge_color).value<QColor>();
  back_color = settings->value("back_color", back_color).value<QColor>();
  vertex_color = settings->value("vertex_color").value<QColor>();

  xS = settings->value("xS", 1.0).toDouble();
  yS = settings->value("yS", 1.0).toDouble();
  zS = settings->value("zS", 1.0).toDouble();

  xRot = settings->value("xRot", 0.0).toDouble();
  yRot = settings->value("yRot", 0.0).toDouble();
  zRot = settings->value("zRot", 0.0).toDouble();

  xMov = settings->value("xMov", 0.0).toDouble();
  yMov = settings->value("yMov", 0.0).toDouble();
  zMov = settings->value("zMov", 0.0).toDouble();

  frust =
      settings->value("frust", 1).toInt();  // не работает (для выбора проекции)

  index_line = settings->value("index_line", 0).toInt();
  index_dot = settings->value("index_dot", 0).toInt();
  widthLine = settings->value("widthLine", 1).toInt();
  sizePoint = settings->value("sizePoint", 0).toInt();

  settings->endGroup();
}
