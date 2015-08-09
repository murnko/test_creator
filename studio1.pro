#-------------------------------------------------
#
# Project created by QtCreator 2015-05-20T14:44:57
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = libharu
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp
HEADERS += \
    main.h
INCLUDEPATH +=/usr/local/include
INCLUDEPATH +=/home/murnko/Downloads/libharu-libharu-a83bd80/demo/

LIBS += -L/usr/local/lib -lhpdf
LIBS += -L/home/murnko/Downloads/libharu-libharu-a83bd80/demo/ -grid_sheet

DISTFILES += \
    komentarz.txt
