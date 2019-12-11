#pragma once

#include <QtWidgets/QMainWindow>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

class QOpenGLTest : public QOpenGLWidget
    , protected QOpenGLFunctions
{
    Q_OBJECT
private:
    QOpenGLShaderProgram shaderProgram;
    QOpenGLBuffer vbo, ebo;
    QOpenGLVertexArrayObject vao;
public:
    QOpenGLTest(QWidget *parent = Q_NULLPTR);

private:
protected:
    virtual void initializeGL() override;


    virtual void resizeGL(int w, int h) override;


    virtual void paintGL() override;

};
