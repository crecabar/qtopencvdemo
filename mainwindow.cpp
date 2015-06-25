#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionStart_triggered()
{
    if(!mCapture.isOpened())
        if(!mCapture.open(0))
            return;
    startTimer(50);
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    cv::Mat image;
    mCapture >> image;

    if(mFlipVert && mFlipHoriz)
        cv::flip(image, image, -1);
    else if(mFlipVert)
        cv::flip(image, image, 0);
    else if(mFlipHoriz)
        cv::flip(image, image, 1);

    ui->openCVviewer->showImage(image);
}

void MainWindow::on_actionVertical_Flip_triggered(bool checked)
{
    mFlipVert = checked;
}

void MainWindow::on_actionHorizontal_Mirror_triggered(bool checked)
{
    mFlipHoriz = checked;
}
