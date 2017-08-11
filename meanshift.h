#ifndef MEANSHIFT_H
#define MEANSHIFT_H

#include <opencv2/opencv.hpp>
#include <QImage>
#include <QDebug>

using namespace cv;

class MeanShift
{
public:
    MeanShift();
    void setTarget(Mat &target, int minSaturation);
    int tracking(Mat &currentImage, Rect &currentRect, Mat &backImage, int minSaturation); //停止條件在此加入
    void QImageToCvMat(const QImage &inImage, cv::Mat &dst);

private:
    void getTask(Mat &src, Mat &hsv, Mat &hue, Mat &mask, int minSaturation);
    MatND getHueHist(Mat &hue, Mat &mask);
    MatND targetHist;
    float hue_range[2];
    const float* ranges;
};

#endif // MEANSHIFT_H
