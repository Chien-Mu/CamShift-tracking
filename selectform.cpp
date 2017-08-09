#include "selectform.h"
#include "ui_selectform.h"

#include <QPainter>

SelectForm::SelectForm(QWidget *parent) : QWidget(parent), ui(new Ui::SelectForm){
    ui->setupUi(this);

    this->Wratio = (float)PAINT_WIDTH/(float)IMAGE_WIDTH;
    this->Hratio = (float)PAINT_HEIGTH/(float)IMAGE_HEIGTH;

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(complete()));
}

void SelectForm::setImage(QImage *image){
    this->image = image->copy();
    repaint();
}

void SelectForm::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawImage(0,0,image.scaled(this->size()));

    pen.setBrush(Qt::green);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawRect(proi.ROI);
}

void SelectForm::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        this->proi.MP = event->pos(); //default
        this->proi.PP = event->pos();
    }
}

void SelectForm::mouseMoveEvent(QMouseEvent *event){
    this->proi.MP = event->pos();

    this->proi.ROI.setX(this->proi.PP.x());
    this->proi.ROI.setY(this->proi.PP.y());
    this->proi.ROI.setWidth(this->proi.MP.x() - this->proi.PP.x());
    this->proi.ROI.setHeight(this->proi.MP.y() - this->proi.PP.y());
    repaint();
}

void SelectForm::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
    }
}

void SelectForm::complete(){
    if(proi.ROI.width() == 0 || proi.ROI.height() == 0){
        this->close();
        return;
    }

    emit throwTatget(image.copy(proi.ROI.x() / Wratio,
                                proi.ROI.y() / Hratio,
                                proi.ROI.width() / Wratio,
                                proi.ROI.height() / Hratio));

    this->close();
}

SelectForm::~SelectForm()
{
    delete ui;
}
