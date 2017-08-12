#include "myprocthread.h"

MyProcThread::MyProcThread(MainWindow *ref){
    this->quit = false;
    this->ref = ref;
    this->changeRect = false;
    this->Wratio = (float)PAINT_WIDTH/(float)IMAGE_WIDTH;
    this->Hratio = (float)PAINT_HEIGTH/(float)IMAGE_HEIGTH;

    BIV = new BackImageViewer;
    BIV->show();

    MS = new MeanShift;
    this->targetMinSat = 160;
    this->backprojMinSat = -1;
}

void MyProcThread::stop(){
    this->quit = true;
}

void MyProcThread::targetSlot(QImage image, QRect targetRect){
    Mat target;
    MS->QImageToCvMat(image,target);
    MS->setTarget(target,targetMinSat);
    this->targetRect = targetRect;
    this->changeRect = true;
}

void MyProcThread::run(){
    this->quit = false;

    QImage currentImage;
    Mat cvCurrentImage;
    Rect cvRect;

    while (!quit) {

        /// 如果有更變，才改cvRect
        if(changeRect){
            cvRect.x = targetRect.x();
            cvRect.y = targetRect.y();
            cvRect.width = targetRect.width();
            cvRect.height = targetRect.height();
            changeRect = false; //default
        }

        /// width height 一項等於0 meanshift 會當
        if(cvRect.width == 0 || cvRect.height == 0){
             msleep(300);
             continue;
        }

        /// 取圖
        currentImage = ref->on_Capture().copy(); //by MyVideoSurface 的 currentImage value(copy)
        MS->QImageToCvMat(currentImage, cvCurrentImage);

        /// 追蹤
        Mat cvBackImage;
        MS->tracking(cvCurrentImage, cvRect, cvBackImage, backprojMinSat);

        /// show back image
        QImage qback((const uchar *)cvBackImage.data,
                     cvBackImage.cols,
                     cvBackImage.rows,
                     cvBackImage.step,
                     QImage::Format_Grayscale8);
        qback = qback.scaled(PAINT_WIDTH,PAINT_HEIGTH);
        BIV->setImage(qback);

        // sent rect
        emit trackResult(QRect(cvRect.x * Wratio,
                               cvRect.y * Hratio,
                               cvRect.width, cvRect.height));
    }
}
