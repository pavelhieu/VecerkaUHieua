#-------------------------------------------------
#
# Project created by QtCreator 2017-09-29T21:47:40
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Vecerka
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    dialogzame.cpp \
    dialogusek.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    dialogzame.h \
    dialogusek.h

FORMS    += mainwindow.ui \
    dialog.ui \
    dialogzame.ui \
    dialogusek.ui
