#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/highgui/highgui.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionStart_triggered();

    void on_actionVertical_Flip_triggered(bool checked);

    void on_actionHorizontal_Mirror_triggered(bool checked);

private:
    Ui::MainWindow *ui;
    cv::VideoCapture mCapture;

protected:
    void timerEvent(QTimerEvent *event);

private:
    bool mFlipVert;
    bool mFlipHoriz;
};

#endif // MAINWINDOW_H
