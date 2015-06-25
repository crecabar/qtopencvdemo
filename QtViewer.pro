#-------------------------------------------------
#
# Project created by QtCreator 2015-06-24T12:42:19
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtViewer
TEMPLATE = app

INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib -lopencv_core -lopencv_highgui


SOURCES += main.cpp\
        mainwindow.cpp \
    cqtopencvviewergl.cpp

HEADERS  += mainwindow.h \
    cqtopencvviewergl.h

FORMS    += mainwindow.ui
