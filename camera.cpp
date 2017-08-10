#include "camera.h"
#include <QDebug>
#include <QMessageBox>

Camera::Camera()
{
    //統一解析度
    /*C310 Support
     * 320X240
     * 640X480
     * 1280 X 720
     * 5.0MP (軟體增強處理) */
    this->imageSize.setWidth(IMAGE_WIDTH);
    this->imageSize.setHeight(IMAGE_HEIGTH);
}

void Camera::setCamera(QByteArray deviceName){
    if(deviceName == "")
        cameraDevice = new QCamera; //QCamera 控制相機用
    else
        cameraDevice = new QCamera(deviceName);

    connect(cameraDevice,SIGNAL(error(QCamera::Error)),this,SLOT(on_cameraError()));

    //viewfinder
    videoWidget = new VideoWidget(imageSize);
    cameraDevice->setViewfinder(videoWidget->refVideoSurface());

    //設定捕捉模式
    cameraDevice->setCaptureMode(QCamera::CaptureStillImage);

    //設定捕捉過程
    imageCapture = new QCameraImageCapture(cameraDevice);
    imageCapture->setCaptureDestination(QCameraImageCapture::CaptureToBuffer); //選擇將捕抓內容放在 檔案 或 記憶體

    //設定相機抓傳入時解析度
    QImageEncoderSettings imageSettings; //QImageEncoderSettings 為設定影像編碼選項
    //imageSettings.setCodec("image/jpeg");
    imageSettings.setResolution(imageSize);
    imageCapture->setEncodingSettings(imageSettings); //匯入設定影像編碼選項

    //回傳相機支援
    /*
    qDebug() << imageCapture->supportedImageCodecs(); //回傳相機支援的影像編碼格式
    //回傳相繼支援的解析度
    QList<QSize> SupRes = imageCapture->supportedResolutions();
    for(int i =0;i<SupRes.size();i++)
        qDebug() << "width:" + QString::number(SupRes[i].width()) + " height:" + QString::number(SupRes[i].height());
    */



    //================================SINGAL========================================

    //error
    connect(imageCapture,SIGNAL(error(int,QCameraImageCapture::Error,QString)),
            this,SIGNAL(Error(int,QCameraImageCapture::Error,QString)));
}

QImage &Camera::getCurrentImage(){
    /* 這裡取圖時，一定要加 lock ，不然跑個幾小時就會當
       因為底層的程序在跑時，這邊程序又去取圖，有一定的機率會照成，底層正在改圖，這邊正在取圖
       這時候就會照成 segmentation fault */
    videoWidget->refImageSurface()->getlock();
    return videoWidget->refImageSurface()->getCurrentImage();
}

void Camera::drawVideoWidget(INFO info){
	/* 這裡也一樣，在畫圖時，一定要加 lock，不然跑幾個小時就會當
	   因為這邊的程序要改變座標變數時，paint 程序剛好使用此座標變數
	   這時候就會照成 segmentation fault (因為這原因 debug 了 10天..)*/
    videoWidget->lock();
    videoWidget->draw(info);
}

void Camera::CameraStrat(){
    cameraDevice->start();
}

void Camera::CameraStop(){
    if(cameraDevice->isAvailable())
        cameraDevice->stop();
}

void Camera::on_cameraError(){
    QMessageBox::critical(NULL,"Camera error",cameraDevice->errorString());
}
