#include "QOpenGLTest.h"
#include "Shaders.h"
QOpenGLTest::QOpenGLTest(QWidget *parent)
    : QOpenGLWidget(parent)
    , vbo(QOpenGLBuffer::VertexBuffer),
    ebo(QOpenGLBuffer::IndexBuffer)
{
    resize(800, 600);
}

void QOpenGLTest::initializeGL()
{
    this->initializeOpenGLFunctions();

    bool bSucceed = shaderProgram.addShaderFromSourceCode(QOpenGLShader::Vertex, shaders::vertexShader);
    if (!bSucceed)
    {
        qDebug() << "add Vertex Shader failed \n" << shaderProgram.log();
        return ;
    }
    bSucceed = shaderProgram.addShaderFromSourceCode(QOpenGLShader::Fragment, shaders::fragmentShader);
    if (!bSucceed)
    {
        qDebug() << "add Fragment Shader failed \n" << shaderProgram.log();
        return ;
    }
    shaderProgram.link();

    GLfloat vertices[] = {
        -1.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
    };

    QOpenGLVertexArrayObject::Binder vaoBind(&vao);

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices) * 3 * 3);

    //enable attr
    int attr = -1;
    attr = shaderProgram.attributeLocation("aPos");
    shaderProgram.setAttributeBuffer(attr, GL_FLOAT, 0, 3, sizeof(GLfloat) * 3);
    shaderProgram.enableAttributeArray(attr);

    vbo.release();
}

void QOpenGLTest::resizeGL(int w, int h)
{
}

void QOpenGLTest::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram.bind();
    {
        QOpenGLVertexArrayObject::Binder vaoBind(&vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    shaderProgram.release();
}
