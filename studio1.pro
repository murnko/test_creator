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
CONFIG   += c++11

TEMPLATE = app



SOURCES += main.cpp \
    funkcje.cpp \
    libh.cpp
HEADERS += \
    main.h \
    funkcje.h \
    libh.h
INCLUDEPATH +=/usr/local/include


LIBS += -L/usr/local/lib -lhpdf


DISTFILES += \
    komentarz.txt
