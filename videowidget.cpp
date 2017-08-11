#include "videowidget.h"
#include <QDebug>

VideoWidget::VideoWidget(QSize imageSize, QWidget *parent) : QWidget(parent)
{
    this->imageSize = imageSize; //設定圖像大小
    QSize widgetSize(PAINT_WIDTH,PAINT_HEIGTH); //設定畫版大小(非圖像大小)

    this->Wratio = (float)widgetSize.width()/(float)imageSize.width();
    this->Hratio = (float)widgetSize.height()/(float)imageSize.height();

    this->isPush = true;
    this->isdraw = false;

    surface = new MyVideoSurface(this,widgetSize);
    this->setFixedSize(widgetSize); //如果沒設畫板大小，可能顯示會有問題。
    //-----------以上為不可變動區-------------
    this->rect.setX(0);
    this->rect.setY(0);
    this->rect.setWidth(0);
    this->rect.setHeight(0);
}

VideoWidget::~VideoWidget(){
    delete surface;
}

void VideoWidget::lock(){
    this->isPush = true;
}

void VideoWidget::draw(QRect &rect){
    while(isdraw)
        continue;

    this->rect = rect;

    isPush = false;
}

// paintEvent() 與 draw() 是不同執行緒在使用的
void VideoWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    if (surface->isActive()) {
        surface->Drawing(true);
        QPainter painter; //把widget 當畫板
        painter.begin(this); //實驗這樣把 .begin() .end() 寫出來效率會更快
        surface->paintImage(&painter); //從記憶體取得圖

        //draw
        pen.setBrush(Qt::red);
        pen.setWidth(2);
        painter.setPen(pen);
        if(!isPush){
        	/* 加 isdraw 的重要性超大
        	   一定有機率會跑進來後，draw()才執行，所以裡面還要再加保護
        	   避免 draw() 改值
        	   當初因為這原因 搞了很久..*/
            isdraw = true;
            painter.drawRect(rect); //在畫上矩形
            isdraw = false;
        }

        painter.end();
        surface->Drawing(false);
    }
}
