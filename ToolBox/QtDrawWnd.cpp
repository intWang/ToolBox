#include "QtDrawWnd.h"
QtDrawWnd::QtDrawWnd(QWidget *parent)
    : QOpenGLWidget(parent)
    ,vbo(QOpenGLBuffer::VertexBuffer),
    ebo(QOpenGLBuffer::IndexBuffer)
{
}

QtDrawWnd::~QtDrawWnd()
{
    makeCurrent();

    vbo.destroy();
    ebo.destroy();
    vao.destroy();

    doneCurrent();
}
// const char* pVertiex= R"(#version 330 core
// layout(location = 0) in vec3 aPos;
// void main(){
//     gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
// })";

const char* pVertiex = R"(#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 outColor;
void main()
{
    gl_Position = vec4(aPos, 1.0);
    outColor = aColor;
})";

const char* pFrag = R"(#version 330 core
out vec4 FragColor;
in vec3 outColor;
void main(){
    FragColor = vec4(outColor, 1.0f);
})";
void QtDrawWnd::initializeGL()
{
    this->initializeOpenGLFunctions();

    bool success = shaderProgram.addShaderFromSourceCode(QOpenGLShader::Vertex, pVertiex);
    if (!success) {
        qDebug() << "shaderProgram addShaderFromSourceFile failed!" << shaderProgram.log();
        return;
    }

    success = shaderProgram.addShaderFromSourceCode(QOpenGLShader::Fragment, pFrag);
    if (!success) {
        qDebug() << "shaderProgram addShaderFromSourceFile failed!" << shaderProgram.log();
        return;
    }

    success = shaderProgram.link();
    if (!success) {
        qDebug() << "shaderProgram link failed!" << shaderProgram.log();
    }

    //VAO，VBO数据部分
    GLfloat vertices[] = {
        //point              //color
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // rb
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // lb
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // t
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    QOpenGLVertexArrayObject::Binder vaoBind(&vao);

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));
// 
//     ebo.create();
//     ebo.bind();
//     ebo.allocate(indices, sizeof(indices));

    int attr = -1;
    attr = shaderProgram.attributeLocation("aPos");
    shaderProgram.setAttributeBuffer(attr, GL_FLOAT, 0, 6, sizeof(GLfloat) * 6);
    shaderProgram.enableAttributeArray(attr);

    attr = shaderProgram.attributeLocation("aColor");
    shaderProgram.setAttributeBuffer(attr, GL_FLOAT,  3, 6, sizeof(GLfloat) * 6);
    shaderProgram.enableAttributeArray(attr);

    vbo.release();
    //    remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //    ebo.release();
}

void QtDrawWnd::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void QtDrawWnd::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram.bind();
    {
        QOpenGLVertexArrayObject::Binder vaoBind(&vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        qDebug() << glGetError();
    }
    shaderProgram.release();
}
