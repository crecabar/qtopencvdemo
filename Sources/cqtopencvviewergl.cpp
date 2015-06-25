#include "cqtopencvviewergl.h"
#include <QOpenGLFunctions>

CQtOpenCVViewerGl::CQtOpenCVViewerGl(QWidget *parent) :
    QOpenGLWidget(parent)
{
    mSceneChanged = false;
    mBgColor = QColor::fromRgb(150, 150, 150);

    mOutH = 0;
    mOutW = 0;
    mImgratio = 4.0f/3.0f; // Default image ratio

    mPosX = 0;
    mPosY = 0;
}

void CQtOpenCVViewerGl::initializeGL()
{
    makeCurrent();

    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    float r = ((float)mBgColor.darker().red())/255.0f;
    float g = ((float)mBgColor.darker().green())/255.0f;
    float b = ((float)mBgColor.darker().blue())/255.0f;
    f->glClearColor(r, g, b, 1.0f);
}

void CQtOpenCVViewerGl::resizeGL(int width, int height)
{
    makeCurrent();
    glViewport(0, 0, (GLint)width, (GLint)height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, width, 0, height, 0, 1); // To Draw image in the center of the area

    glMatrixMode(GL_MODELVIEW);

    // --- > Scaled Image Sizes
    mOutH = width/mImgratio;
    mOutW = width;

    if(mOutH > height) {
        mOutW = height*mImgratio;
        mOutH = height;
    }

    emit imageSizeChanged(mOutW, mOutH);
    // < --- Scaled Image Sizes

    mPosX = (width-mOutW)/2;
    mPosY = (height-mOutH)/2;

    mSceneChanged = true;
    updateScene();
}

void CQtOpenCVViewerGl::updateScene()
{
    if(mSceneChanged && this->isVisible())
        update();
}

void CQtOpenCVViewerGl::paintGL()
{
    makeCurrent();

    if(!mSceneChanged)
        return;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderImage();

    mSceneChanged = false;
}

void CQtOpenCVViewerGl::renderImage()
{
    makeCurrent();

    glClear(GL_COLOR_BUFFER_BIT);

    if(!mRenderQtImg.isNull()) {
        glLoadIdentity();

        QImage image; // the image rendered
        glPushMatrix();
        {
            int imW = mRenderQtImg.width();
            int imH = mRenderQtImg.height();

            if(imW != this->size().width() &&
                    imH != this->size().height()) {
                image = mRenderQtImg.scaled(QSize(mOutW, mOutH),
                                            Qt::IgnoreAspectRatio,
                                            Qt::SmoothTransformation);
            }
            else
                image = mRenderQtImg;

            // ---> Centering image in draw area
            glRasterPos2i(mPosX, mPosY);
            // <--- Centering image in draw area

            imW = image.width();
            imH = image.height();

            glDrawPixels(imW, imH, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
        }
        glPopMatrix();

        //end
        glFlush();
    }
}

bool CQtOpenCVViewerGl::showImage(cv::Mat image)
{
    image.copyTo(mOrigImage);

    mImgratio = (float)image.cols/(float)image.rows;

    if(mOrigImage.channels() == 3)
        mRenderQtImg = QImage((const unsigned char*)(mOrigImage.data),
                              mOrigImage.cols, mOrigImage.rows,
                              mOrigImage.step, QImage::Format_RGB888);
    else if(mOrigImage.channels() == 1)
        mRenderQtImg = QImage((const unsigned char*)(mOrigImage.data),
                              mOrigImage.cols, mOrigImage.rows,
                              mOrigImage.step, QImage::Format_Indexed8);
    else
        return false;

    //mRenderQtImg = QOpenGLWidget::convertToGLFormat(mRenderQtImg);
    mSceneChanged = true;

    updateScene();
    return true;
}
