#include "meanshift.h"

MeanShift::MeanShift(MainWindow *ref){
    this->quit = false;

    hue_range[0] = 0.0;
    hue_range[1] = 179.0; //hue的強度範圍在 180
    ranges = hue_range;
}

void MeanShift::run(){
    while(quit){
        ref->
    }
}

void MeanShift::setTarget(Mat target, int minSaturation = -1){
    this->target = target;

    Mat hsv,hue,mask;
    getTask(target,hsv,hue,mask,minSaturation);

    this->targetHist = getHueHist(hue,mask);
}

int MeanShift::track(Mat &currentImage, Rect &currentRect, int minSaturation = -1){
    Mat hsv,hue,mask;

    getTask(currentImage,hsv,hue,mask,minSaturation);

    /// Get Backprojection (圖跟圖去做對比)
    MatND backproj;
    calcBackProject( &hue, 1, 0, this->targetHist, backproj, &ranges, 1, true );

    /// 針對 Saturation 的位置過濾
    if(minSaturation != -1)
        bitwise_and(backproj, mask, backproj);


    rectangle(backproj, currentRect, Scalar(255)); //draw (移動前)

    /// mean Shfit
    TermCriteria criteria(TermCriteria::COUNT | TermCriteria::EPS, 10, 0.01); //停止條件
    int shift = meanShift(backproj, currentRect, criteria);

    rectangle(backproj, currentRect, Scalar(255)); //draw (移動後)
    imshow( "BackProj", backproj );
    return shift;
}

void MeanShift::getTask(Mat &src, Mat &hsv, Mat &hue, Mat &mask, int minSaturation){
    /// get hsv
    cvtColor( src, hsv, CV_BGR2HSV );  //注意 CV_BGR2HSV 與 CV_RGB2HSV 轉出來的會不一樣

    /// channels 分配
    hue.create(hsv.size() ,hsv.depth());
    mask.create(hsv.size() , hsv.depth());
    Mat dst[] = { hue, mask };
    int fromTo[] = { 0,0 ,1,1 };
    mixChannels(&hsv, 1, dst, 2, fromTo, 2);

    /// 標記飽和度位置
    if(minSaturation != -1)
        threshold(mask, mask, minSaturation, 255, THRESH_BINARY);
    else
        mask = Mat();
}

MatND MeanShift::getHueHist(Mat &hue, Mat &mask){

    /// 直方圖統計 hue
    MatND hist;
    int histSize = 180;  //使用"較粗糙"的數量去和，出現的機率會較高，如果用180比去和就等於要符合這180筆資料，機率就較低
    calcHist( &hue, 1, 0, mask, hist, 1, &histSize, &ranges);
    normalize( hist, hist, 0, 255, NORM_MINMAX, -1, Mat() );

    /// 畫出 hue 的直方圖 方便觀看
    int w = 400; int h = 400;
    int bin_w = cvRound( (double) w / histSize );
    Mat histImg = Mat::zeros( w, h, CV_8UC3 );
    for( int i = 0; i < histSize; i ++ )
        rectangle( histImg, Point( i*bin_w, h ), Point( (i+1)*bin_w, h - cvRound( hist.at<float>(i)*h/255.0 ) ), Scalar( 0, 0, 255 ), -1 );
    imshow( "Histogram", histImg );

    return hist;
}

Mat MeanShift::QImageToCvMat(const QImage &inImage, bool inCloneImageData){
    /* 以下 BGR 排列已實驗過，註解無誤 */
    switch (inImage.format()){
    case QImage::Format_RGB32:      // 8-bit, 4 channel
    {
        cv::Mat  mat( inImage.height(),
                      inImage.width(),
                      CV_8UC4,      //QImage 轉 Mat CV_8UC4 預設排列就是 BGRA (不是RGBA)
                      const_cast<uchar*>(inImage.bits()),
                      inImage.bytesPerLine() );
        return (inCloneImageData ? mat.clone() : mat);
    }
    case QImage::Format_RGB888:     // 8-bit, 3 channel
    {
        if ( !inCloneImageData )    //一定要 clone
            qWarning() << "ASM::QImageToCvMat() - Conversion requires cloning since we use a temporary QImage";
        QImage   swapped = inImage.rgbSwapped();  //QImage 預設是 RGB，rgbSwapped() 為轉成 BGR
        return cv::Mat( swapped.height(),
                        swapped.width(),
                        CV_8UC3,    //QImage 轉 Mat CV_8UC3 預設排列是 RGB (不是BGR)，所以才要用 rgbSwapped() 特別轉
                        const_cast<uchar*>(swapped.bits()),
                        swapped.bytesPerLine() ).clone();
    }
    case QImage::Format_Indexed8:   // 8-bit, 1 channel
    {
        cv::Mat  mat( inImage.height(),
                      inImage.width(),
                      CV_8UC1,
                      const_cast<uchar*>(inImage.bits()),
                      inImage.bytesPerLine() );
        return (inCloneImageData ? mat.clone() : mat);
    }

    default:
        qWarning() << "ASM::QImageToCvMat() - QImage format not handled in switch:" << inImage.format();
        break;
    }
    return cv::Mat();
}
