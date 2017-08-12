#include "backimageviewer.h"
#include "ui_backimageviewer.h"
#include <QPainter>

BackImageViewer::BackImageViewer(QWidget *parent) : QWidget(parent), ui(new Ui::BackImageViewer){
    ui->setupUi(this);
}

void BackImageViewer::setImage(QImage &image){
    this->currentImage = image;
    this->update();  //repainter 是強制 repainter 會閃頻、當掉
}

void BackImageViewer::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    if(currentImage.isNull())
        return;

    QPainter painter(this);
    painter.drawImage(0,0,currentImage);
}

BackImageViewer::~BackImageViewer()
{
    delete ui;
}
