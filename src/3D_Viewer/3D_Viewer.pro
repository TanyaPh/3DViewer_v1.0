QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Back.c \
    ../s21_matrix.c \
    QtGifImage-master/src/3rdParty/giflib/dgif_lib.c \
    QtGifImage-master/src/3rdParty/giflib/egif_lib.c \
    QtGifImage-master/src/3rdParty/giflib/gif_err.c \
    QtGifImage-master/src/3rdParty/giflib/gif_font.c \
    QtGifImage-master/src/3rdParty/giflib/gif_hash.c \
    QtGifImage-master/src/3rdParty/giflib/gifalloc.c \
    QtGifImage-master/src/3rdParty/giflib/quantize.c \
    QtGifImage-master/src/gifimage/qgifimage.cpp \
    glview.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../Back.h \
    ../s21_matrix.h \
    QtGifImage-master/src/3rdParty/giflib/gif_hash.h \
    QtGifImage-master/src/3rdParty/giflib/gif_lib.h \
    QtGifImage-master/src/3rdParty/giflib/gif_lib_private.h \
    QtGifImage-master/src/gifimage/qgifglobal.h \
    QtGifImage-master/src/gifimage/qgifimage.h \
    QtGifImage-master/src/gifimage/qgifimage_p.h \
    glview.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

win32:RC_ICONS += 3d_icon.ico
macx: ICON = 3d_icon.icns

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    QtGifImage-master/examples/examples.pro \
    QtGifImage-master/examples/gifimage/creategif/creategif.pro \
    QtGifImage-master/examples/gifimage/extractFrames/extractFrames.pro \
    QtGifImage-master/examples/gifimage/gifimage.pro \
    QtGifImage-master/qtgifimage.pro \
    QtGifImage-master/src/gifimage/doc/snippets/doc_src_qtgifimage.pro \
    QtGifImage-master/src/gifimage/gifimage.pro \
    QtGifImage-master/src/src.pro \
    QtGifImage-master/tests/auto/auto.pro \
    QtGifImage-master/tests/auto/qgifimage/qgifimage.pro \
    QtGifImage-master/tests/tests.pro

DISTFILES += \
    QtGifImage-master/README.md \
    QtGifImage-master/examples/gifimage/creategif/doc/images/demo1.gif \
    QtGifImage-master/examples/gifimage/creategif/doc/src/creategif.qdoc \
    QtGifImage-master/examples/gifimage/extractFrames/doc/src/extractframes.qdoc \
    QtGifImage-master/examples/gifimage/extractFrames/test.gif \
    QtGifImage-master/index.qdoc \
    QtGifImage-master/mkspecs/modules-inst/qt_lib_gifimage.pri \
    QtGifImage-master/mkspecs/modules-inst/qt_lib_gifimage_private.pri \
    QtGifImage-master/mkspecs/modules/qt_lib_gifimage.pri \
    QtGifImage-master/qtgifimage.qdoc \
    QtGifImage-master/src/3rdParty/giflib.pri \
    QtGifImage-master/src/3rdParty/giflib/AUTHORS \
    QtGifImage-master/src/3rdParty/giflib/COPYING \
    QtGifImage-master/src/3rdParty/giflib/README \
    QtGifImage-master/src/gifimage/doc/qtgifimage.qdocconf \
    QtGifImage-master/src/gifimage/doc/src/examples.qdoc \
    QtGifImage-master/src/gifimage/doc/src/index.qdoc \
    QtGifImage-master/src/gifimage/doc/src/qtgifimage.qdoc \
    QtGifImage-master/src/gifimage/doc/src/usage.qdoc \
    QtGifImage-master/src/gifimage/qdoc_wrapper.sh \
    QtGifImage-master/src/gifimage/qtgifimage.pri \
    QtGifImage-master/sync.profile \
    QtGifImage-master/tests/auto/qgifimage/test.gif
