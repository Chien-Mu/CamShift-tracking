#ifndef SHARED_H
#define SHARED_H

#include <QDebug>
#include <QDateTime>
#define PAINT_WIDTH 640
#define PAINT_HEIGTH 480
#define IMAGE_WIDTH 1280
#define IMAGE_HEIGTH 720

class Shared
{
public:
    Shared();
    QString getDate();
    QString getDateTime();
    QString getDateTime_FILE();
    QString getDateTime_print();
    QString getDateTime_yesterday_FILE();
};

#endif // SHARED_H
