#include "backimageviewer.h"
#include "ui_backimageviewer.h"
#include <QPainter>

BackImageViewer::BackImageViewer(QWidget *parent) : QWidget(parent), ui(new Ui::BackImageViewer){
    ui->setupUi(this);
}

void BackImageViewer::setImage(QImage image){
    this->currentImage = image;
    repaint();
}

void BackImageViewer::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    if(currentImage.isNull())
        return;

    QPainter painter(this);
    painter.drawImage(0,0,currentImage.scaled(this->size()));
}

BackImageViewer::~BackImageViewer()
{
    delete ui;
}
