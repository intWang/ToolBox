#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QWidget>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class QtDrawWnd : public QOpenGLWidget
    , protected QOpenGLFunctions
{
    Q_OBJECT

protected:
    QSize mFrameSize;
    QColor mBackground;
    QOpenGLShaderProgram shaderProgram;
    QOpenGLBuffer vbo, ebo;
    QOpenGLVertexArrayObject vao;
public:
    QtDrawWnd(QWidget *parent);
    ~QtDrawWnd();

    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;
};


using PDrawWnd = QtDrawWnd * ;
