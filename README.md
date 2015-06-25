# Qt Viewer Demo
A simple demo from a tutorial, creating an application using Qt 5.4, OpenGL and OpenCV.

## Compiling and usage
For test this project clone into any dir in your computer:
```
$ mkdir QtViewer
$ cd QtViewer
$ git clone https://github.com/crecabar/qtopencvdemo.git
$ mkdir build
```
Then edit the QtViewer.pro.sample to match with your local dirs for OpenCV and save it as QtViewer.pro:
```
$ vi QtViewer/QtViewer.pro.sample
```
QtViewer.pro.sample:
```
QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtViewer
TEMPLATE = app

SOURCES += Sources/main.cpp\
    Sources/mainwindow.cpp \
    Sources/cqtopencvviewergl.cpp

HEADERS  += Headers/mainwindow.h \
    Headers/cqtopencvviewergl.h

FORMS    += Forms/mainwindow.ui

INCLUDEPATH += Headers

# External libraries
INCLUDEPATH += <your path to opencv includes>
LIBS += -L<your path to opencv libraries> -lopencv_core -lopencv_highgui
```
And finnaly compile:
```
$ cd build
$ qmake ../QtViewer/QtViewer.pro
$ make
```
Enjoy it!
