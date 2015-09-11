#-------------------------------------------------
#
# Project created by QtCreator 2015-08-28T09:47:32
#
#-------------------------------------------------

#include(qxtglobalshortcut5/qxt.pri)

QT       += core gui
QT       += webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chinasoDestopTool
TEMPLATE = app

#QMAKE_LFLAGS += /MANIFESTUAC:"level='requireAdministrator'uiAccess='false'"
QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01


SOURCES += main.cpp\
        dialog.cpp

HEADERS  += dialog.h

FORMS    += dialog.ui

RESOURCES += \
    image.qrc


