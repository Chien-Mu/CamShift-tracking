#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMessageBox>
#include <QCameraInfo>
#include <QSpacerItem>

#include "scanthread.h"
scanthread *scanner;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //為了讓camera在中心
    QSpacerItem * H_spacer = new QSpacerItem(1000,0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSpacerItem * H_spacer_2 = new QSpacerItem(1000,0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->gridLayout->addItem(H_spacer,0,0);
    ui->gridLayout->addItem(H_spacer_2,0,2);

    //camera
    camera = new Camera;

    //scanner
    scanner = new scanthread(this);
    connect(camera,SIGNAL(Error(int,QCameraImageCapture::Error,QString)),
            this,SLOT(displayCaptureError(int,QCameraImageCapture::Error,QString)));

    //initialization
    initialization();

    //draw(一定要在 initialization() 之後)
    qRegisterMetaType<INFO>("INFO");
    /* 下面設定 BlockingQueuedConnection 是重點！ (他會 blocking emit 的地方，直到 slot 處理完)
       一定要等 paint 值送到在繼續處理，不然跑幾小時就當了，因為這原因 debug 好久..*/
    connect(scanner,SIGNAL(throwInfo(INFO)),camera,SLOT(drawVideoWidget(INFO)),Qt::BlockingQueuedConnection);

    //select tatget widget
    SF = new SelectForm;

    //ui
    formText = new QPlainTextEdit(this);
    ui->gridLayout->addWidget(formText,1,0,1,3);
    ui->gridLayout->addWidget(camera->getVideoWidget(),0,1); //一定要在 initialization() 之後

    //menu
    connect(ui->menuBar,SIGNAL(triggered(QAction*)),this,SLOT(trigerMenu(QAction*)));
}

bool MainWindow::initialization(){
    //列出相機
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    qDebug() << cameras[0].deviceName(); //設備id
    qDebug() << cameras[0].description(); //設備名稱

    //camera set
    camera->setCamera(cameras[0].deviceName().toLocal8Bit());
    camera->CameraStrat();

    scanner->start();

    return true;
}

void MainWindow::trigerMenu(QAction *act){
    if(act->text() == "Target"){
        SF->setImage(on_Capture());
        SF->show();
        SF->raise();
    }else if(act->text() == "Config"){
        qDebug() << "C";
    }
}

void MainWindow::start(){
    if(scanner->isRunning())
        return;

    initialization();
}

void MainWindow::stop(){
    camera->CameraStop();
    scanner->stop();
    qDebug() << "stop";
}

QImage &MainWindow::on_Capture(){
    return camera->getCurrentImage(); //by MyVideoSurface 的 currentImage reference
}

void MainWindow::displayCaptureError(int id, QCameraImageCapture::Error error, const QString &errorString){
    Q_UNUSED(id);
    Q_UNUSED(error);
    QMessageBox::warning(this, tr("Image Capture Error"), errorString);
}

MainWindow::~MainWindow()
{
    stop();
    delete ui;
}
