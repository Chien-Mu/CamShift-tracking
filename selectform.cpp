#include "selectform.h"
#include "ui_selectform.h"

SelectForm::SelectForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectForm)
{
    ui->setupUi(this);
}

SelectForm::~SelectForm()
{
    delete ui;
}
