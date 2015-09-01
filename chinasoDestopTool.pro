#-------------------------------------------------
#
# Project created by QtCreator 2015-08-28T09:47:32
#
#-------------------------------------------------

QT       += core gui
QT       += webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chinasoDestopTool
TEMPLATE = app



SOURCES += main.cpp\
        dialog.cpp

HEADERS  += dialog.h

FORMS    += dialog.ui

RESOURCES += \
    image.qrc


include(qxtglobalshortcut5/qxt.pri)
