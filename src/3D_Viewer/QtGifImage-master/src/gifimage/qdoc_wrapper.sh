#!/bin/bash
QT_VERSION=0.1.0
export QT_VERSION
QT_VER=0.1
export QT_VER
QT_VERSION_TAG=010
export QT_VERSION_TAG
QT_INSTALL_DOCS=/usr/local/share/qt/doc
export QT_INSTALL_DOCS
BUILDDIR=/opt/goinfre/acoustic/C8_3DViewer_v1.0-1/src/3D_Viewer_New/QtGifImage-master/src/gifimage
export BUILDDIR
exec /usr/local/bin/qdoc "$@"
