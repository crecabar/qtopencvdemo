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
    if(!mCapture1.isOpened() || !mCapture2.isOpened())
        if(!mCapture1.open(1) || !mCapture2.open(2))
            return;
    startTimer(50);
}

void MainWindow::on_actionStop_triggered()
{
    if(mCapture1.isOpened() || mCapture2.isOpened()) {
        mCapture1.release();
        mCapture2.release();
    }
    return;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    cv::Mat image1, image2;
    mCapture1 >> image1;
    mCapture2 >> image2;
    cv::flip(image1, image1, -1);
    cv::flip(image2, image2, -1);
    /*
    if(mFlipVert && mFlipHoriz)
        cv::flip(image1, image1, -1);
    else if(mFlipVert)
        cv::flip(image1, image1, 0);
    else if(mFlipHoriz)
        cv::flip(image1, image1, 1);
    */
    std::cout << "Left frame" << std::endl;
    ui->openCVviewer->showImage(image1);
    usleep(30);
    std::cout << "Right frame" << std::endl;
    ui->openCVviewer->showImage(image2);
    usleep(30);
}

void MainWindow::on_actionVertical_Flip_triggered(bool checked)
{
    mFlipVert = checked;
}

void MainWindow::on_actionHorizontal_Mirror_triggered(bool checked)
{
    mFlipHoriz = checked;
}
