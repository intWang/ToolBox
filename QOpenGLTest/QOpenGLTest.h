#pragma once

#include <QtWidgets/QMainWindow>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QCamera>
#include "QtCameraCapture.h"
#include <QMutex>
class QOpenGLTest : public QOpenGLWidget
    , protected QOpenGLFunctions
{
    Q_OBJECT
private:
    QOpenGLShaderProgram shaderProgram;
    QOpenGLBuffer vbo, ebo;
    QOpenGLVertexArrayObject vao;
    QOpenGLTexture tex;
    QOpenGLTexture* pTex = nullptr;
    QtCameraCapture* pcampture = nullptr;
    //camera
    QCamera camera;
    QMutex mxProcess;
    QSize mFrameSize;

    float mViewAspect;
    float mVideoAspect;
    float mScaleFactor;
public:
    QOpenGLTest(QWidget *parent = Q_NULLPTR);
    ~QOpenGLTest();
private:
    void InitShaders();
    void InitVertex();
    void LoadTexture(QVideoFrame& framData);
    void LoadTexture(QString strPicDir);
    void InitCamera();
    void UninitCamera();
protected:
    virtual void initializeGL() override;

    virtual void resizeGL(int w, int h) override;

    virtual void paintGL() override;

};
