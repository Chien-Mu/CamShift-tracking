#ifndef MEANSHIFT_H
#define MEANSHIFT_H

#include <opencv2/opencv.hpp>
#include <QImage>
#include <QDebug>

#include "mainwindow.h"

using namespace cv;

class MeanShift : public QThread
{
    Q_OBJECT
public:
    MeanShift(MainWindow *ref);
    void setTarget(Mat target, int minSaturation);
    int track(Mat &currentImage, Rect &currentRect, int minSaturation); //停止條件在此加入
    Mat QImageToCvMat(const QImage &inImage, bool inCloneImageData = true);
    void run();
    void stop();

private:
    MainWindow *ref;
    void getTask(Mat &src, Mat &hsv, Mat &hue, Mat &mask, int minSaturation);
    MatND getHueHist(Mat &hue, Mat &mask);
    Mat target;
    MatND targetHist;
    float hue_range[2];
    const float* ranges;
    bool quit;
};

#endif // MEANSHIFT_H
