#-------------------------------------------------
#
# Project created by QtCreator 2017-04-10T14:03:20
#
#-------------------------------------------------

QT       += core gui
QT       += opengl
QT       += multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CamShift-Tracking
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myvideosurface.cpp \
    videowidget.cpp \
    camera.cpp \
    shared.cpp \
    selectform.cpp \
    myprocthread.cpp \
    meanshift.cpp \
    backimageviewer.cpp

HEADERS  += mainwindow.h \
    myvideosurface.h \
    videowidget.h \
    camera.h \
    shared.h \
    selectform.h \
    myprocthread.h \
    meanshift.h \
    backimageviewer.h

FORMS    += mainwindow.ui \
    selectform.ui \
    backimageviewer.ui

macx{
    #OpenCV
    INCLUDEPATH += /usr/local/opt/opencv3/include
    LIBS += `pkg-config --libs opencv`
}
unix:!macx{
    #Cross Compile
    target.path = /home/pi/test5
    INSTALLS += target
}
win32{
    #preprocessor definition
    DEFINES += WINDOWS
}
