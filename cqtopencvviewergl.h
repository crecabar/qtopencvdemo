#ifndef CQTOPENCVVIEWERGL_H
#define CQTOPENCVVIEWERGL_H

#include <QOpenGLWidget>
#include <opencv2/core/core.hpp>

class CQtOpenCVViewerGl : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit CQtOpenCVViewerGl(QWidget *parent = 0);

signals:
    void imageSizeChanged(int outW, int outH); /// Used to resize image outside the widget

public slots:
    bool showImage(cv::Mat image); /// Used to set the image to be viewed

protected:
    void initializeGL(); /// OpenGL initialization
    void paintGL(); /// OpenGL Rendering
    void resizeGL(int width, int height); /// Widget Resize Event

    void updateScene(); /// Forces a scene update
    void renderImage(); /// Render image on openGL frame

private:
    bool mSceneChanged; /// Indicates when OpenGL view has to be redrawn

    QImage mRenderQtImg; /// Qt  image to be drawn
    cv::Mat mOrigImage; /// original OpenCV image

    QColor mBgColor; /// Background color

    int mOutH; /// Resized Image height
    int mOutW; /// Resised Image width
    float mImgratio; /// height/width ratio

    int mPosX; /// Top left X position to render image in the center of widget
    int mPosY; /// Top left Y position to render image in the center of widget

};

#endif // CQTOPENCVVIEWERGL_H
