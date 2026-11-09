QT       += core gui svg network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_Nav_Data
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cdrone.cpp

HEADERS  += mainwindow.h \
    cdrone.h

FORMS    += mainwindow.ui

win32: LIBS += -L$$PWD/./ -lqfi

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
