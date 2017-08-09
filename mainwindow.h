﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/* 此地方預設使用標記 3*/

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QImage>

#include "camera.h"
#include "shared.h"
#include "selectform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool initialization();
    QImage *on_Capture();
    QImage currentImage;
    void start();
    void stop();

private:
    Ui::MainWindow *ui;
    QPlainTextEdit *formText;
    SelectForm *SF;

    //camera
    Camera *camera;


private slots:
    void displayCaptureError(int id,QCameraImageCapture::Error error,const QString &errorString);
    void trigerMenu(QAction *act);
};

#endif // MAINWINDOW_H
