#ifndef SELECTFORM_H
#define SELECTFORM_H

#include <QWidget>
#include <QPen>
#include <QMouseEvent>
#include <QDebug>

#include "shared.h"

namespace Ui {
class SelectForm;
}

struct PaintROI{
    QPoint PP;  //press point
    QPoint MP;  //move point
    QRect ROI;
};

class SelectForm : public QWidget
{
    Q_OBJECT

public:
    explicit SelectForm(QWidget *parent = 0);
    ~SelectForm();
    void setImage(QImage *image);

protected:
    void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::SelectForm *ui;
    QImage image;
    QPen pen;
    PaintROI proi;
    float Wratio;
    float Hratio;

private slots:
    void complete();

signals:
    void throwTatget(QImage image);
};

#endif // SELECTFORM_H
