QT_MODULE_BIN_BASE = /opt/goinfre/acoustic/C8_3DViewer_v1.0-1/src/3D_Viewer_New/QtGifImage-master/bin
QT_MODULE_INCLUDE_BASE = /opt/goinfre/acoustic/C8_3DViewer_v1.0-1/src/3D_Viewer_New/QtGifImage-master/include
QT_MODULE_LIB_BASE = /opt/goinfre/acoustic/C8_3DViewer_v1.0-1/src/3D_Viewer_New/QtGifImage-master/lib
QT_MODULE_HOST_LIB_BASE = /opt/goinfre/acoustic/C8_3DViewer_v1.0-1/src/3D_Viewer_New/QtGifImage-master/lib
include(/opt/goinfre/acoustic/C8_3DViewer_v1.0-1/src/3D_Viewer_New/QtGifImage-master/mkspecs/modules-inst/qt_lib_gifimage.pri)
QT.gifimage.priority = 1
include(/opt/goinfre/acoustic/C8_3DViewer_v1.0-1/src/3D_Viewer_New/QtGifImage-master/mkspecs/modules-inst/qt_lib_gifimage_private.pri)
QT.gifimage_private.priority = 1
QT.gifimage.includes = $$QT_MODULE_INCLUDE_BASE $$QT_MODULE_INCLUDE_BASE/QtGifImage
QT.gifimage_private.includes = $$QT_MODULE_INCLUDE_BASE/QtGifImage/0.1.0 $$QT_MODULE_INCLUDE_BASE/QtGifImage/0.1.0/QtGifImage
