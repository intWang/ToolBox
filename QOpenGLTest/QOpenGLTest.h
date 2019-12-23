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
#include <QKeyEvent>
#include <QWheelEvent>
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
    std::shared_ptr<QCamera> m_pCamera = nullptr;

    float mViewAspect;
    float mVideoAspect;
    float mScaleFactor;

    QMatrix4x4 mModel;
    QMatrix4x4 mView;
    QMatrix4x4 mProjection;
    QVector3D mCurCamPos = {0,0,3};

public:
    QOpenGLTest(QWidget *parent = Q_NULLPTR);
    ~QOpenGLTest();
private:
    void InitShaders();
    void InitShaders3D();
    void InitVertex();
    void InitVertex3D();
    void LoadTexture(QVideoFrame& framData);
    void LoadTexture(QString strPicDir);
    void InitCamera();
    void Transform(QMatrix4x4& mTrans, const char* szUniformName = "transform");
    void UninitCamera();

    void PaintNormal();
    void Paint3D();
    void Paint3D_MultiCube();

    QMatrix4x4 CalcLookAtMatrix(QVector3D postion, QVector3D target, QVector3D worldUp);
protected:
    virtual void initializeGL() override;

    virtual void resizeGL(int w, int h) override;

    virtual void paintGL() override;

    virtual void keyPressEvent(QKeyEvent *event) override;

    virtual void wheelEvent(QWheelEvent *event) override;

};
