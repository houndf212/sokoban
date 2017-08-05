#-------------------------------------------------
#
# Project created by QtCreator 2017-08-03T13:32:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sokoban
TEMPLATE = app
#CONFIG += console

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp \
    debug_print.cpp \
    board.cpp \
    board_api.cpp \
    test_print.cpp \
    test_console_board.cpp \
    xsb.cpp \
    imagesource.cpp \
    boardwidget.cpp

HEADERS  += \
    elements.h \
    basic_pos.h \
    basic_resize_matrix.h \
    types.h \
    debug_print.h \
    movedirection.h \
    board.h \
    board_api.h \
    xsb.h \
    imagesource.h \
    boardwidget.h

RESOURCES += \
    image.qrc
