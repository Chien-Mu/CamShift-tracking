#ifndef MYPROCTHREAD_H
#define MYPROCTHREAD_H

#include <QThread>

#include "shared.h"
#include "mainwindow.h"
#include "meanshift.h"
#include "backimageviewer.h"

class MyProcThread : public QThread
{
    Q_OBJECT
public:
    MyProcThread(MainWindow *ref);
    void run();
    void stop();

public slots:
    void targetSlot(QImage image, QRect targetRect);

private:
    bool quit;
    MainWindow *ref;
    BackImageViewer *BIV;
    float Wratio;
    float Hratio;
    MeanShift *MS;
    QRect targetRect;
    volatile bool changeRect;
    int targetMinSat,backprojMinSat;

signals:
    void trackResult(QRect rect);

};

#endif // MYPROCTHREAD_H
