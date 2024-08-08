QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#LIBS += -lglut

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../QtgifImage/giflib/dgif_lib.c \
    ../../QtgifImage/giflib/egif_lib.c \
    ../../QtgifImage/giflib/gif_err.c \
    ../../QtgifImage/giflib/gif_font.c \
    ../../QtgifImage/giflib/gif_hash.c \
    ../../QtgifImage/giflib/gifalloc.c \
    ../../QtgifImage/giflib/quantize.c \
    ../../QtgifImage/qgifimage.cc \
    ../../controller/controller.cc \
    ../../model/matrix_t.cc \
    ../../model/model.cc \
    ../../model/parser_file.cc \
    glwidget.cc \
    main.cc \
    mainwindow.cc

HEADERS += \
    ../../QtgifImage/giflib/gif_hash.h \
    ../../QtgifImage/giflib/gif_lib.h \
    ../../QtgifImage/giflib/gif_lib_private.h \
    ../../QtgifImage/qgifglobal.h \
    ../../QtgifImage/qgifimage.h \
    ../../QtgifImage/qgifimage_p.h \
    ../../controller/controller.h \
    ../../model/matrix_t.h \
    ../../model/model.h \
    ../../model/parser_file.h \
    ../../model/structs.h \
    colordata.h \
    glwidget.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    ../../QtgifImage/gifimage.pro

DISTFILES += \
    ../../QtgifImage/giflib/AUTHORS \
    ../../QtgifImage/giflib/COPYING \
    ../../QtgifImage/giflib/README
