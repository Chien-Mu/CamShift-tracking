#ifndef BACKIMAGEVIEWER_H
#define BACKIMAGEVIEWER_H

#include <QWidget>

namespace Ui {
class BackImageViewer;
}

class BackImageViewer : public QWidget
{
    Q_OBJECT

public:
    explicit BackImageViewer(QWidget *parent = 0);
    ~BackImageViewer();
    void setImage(QImage image);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::BackImageViewer *ui;
    QImage currentImage;
};

#endif // BACKIMAGEVIEWER_H
