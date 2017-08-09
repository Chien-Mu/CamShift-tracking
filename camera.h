#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QWidget>
#include <QCamera>
#include <QCameraImageCapture>
#include <QImageEncoderSettings>

#include "videowidget.h"
#include "shared.h"

/* QCamera 官網範例：https://doc.qt.io/qt-5/qtmultimedia-multimediawidgets-camera-camera-cpp.html*/

class Camera : public QObject
{
    Q_OBJECT
public:
    Camera();
    //set
    void setCamera(QByteArray deviceName);
    void CameraStrat();
    void CameraStop();

    //get
    QWidget *getVideoWidget() { return videoWidget; } //丟出畫版
    QImage getCurrentImage(); //丟圖(不使用 標記 4 的情況，就是使用這函式取圖)

public slots:
    void drawVideoWidget(INFO info);

private:
    //camera and control
    QCamera *cameraDevice;
    QCameraImageCapture *imageCapture;
    VideoWidget *videoWidget;

    //屬性
    QSize imageSize;

private slots:
    void on_cameraError();

signals:
    void Error(int id,QCameraImageCapture::Error error,const QString &errorString);
};

#endif // CAMERA_H
