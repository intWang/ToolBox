#pragma once

#include "QtDrawWnd.h"
#include <QCamera>
#include <memory>
#include "QtCameraCapture.h"
#include <QOpenGLTexture>

class QtCameraWnd : public QtDrawWnd
{
    Q_OBJECT
private:
    std::shared_ptr<QCamera> m_pCamera = nullptr;
    QtCameraCapture* m_pCapture = nullptr;
    int mTextureUniformLocations[3] = {0};
    float mViewAspect = 0.0;
    float mVideoAspect = 0.0;
    float mScaleFactor = 1.0;
    QPoint mDragOffset = {0,0};
    QOpenGLTexture* mTextures[3] = { 0 };
public:
    QtCameraWnd(QWidget *parent);
    ~QtCameraWnd();

    bool StartCamera();

    bool StopCamera();

protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    void updateVertexBuffer();
    bool loadFrame(const VideoFrame& frame);
    void destoryFrame();

};
