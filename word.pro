#-------------------------------------------------
#
# Project created by QtCreator 2015-10-04T01:05:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = word
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    document.cpp \
    finddialog.cpp

HEADERS  += mainwindow.h \
    document.h \
    finddialog.h

FORMS    += mainwindow.ui \

RESOURCES += \
    images.qrc
