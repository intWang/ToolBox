#include "QOpenGLTest.h"
#include "Shaders.h"
#include <QByteArray>
QOpenGLTest::QOpenGLTest(QWidget *parent)
    : QOpenGLWidget(parent)
    , vbo(QOpenGLBuffer::VertexBuffer)
    , ebo(QOpenGLBuffer::IndexBuffer)
    , tex(QOpenGLTexture::Target2D)
{
    resize(800, 600);
    pcampture = new QtCameraCapture(this);
    
}

QOpenGLTest::~QOpenGLTest()
{
    makeCurrent();
    UninitCamera();
    vbo.destroy();
    ebo.destroy();
    vao.destroy();
    doneCurrent();

    if (pcampture)
    {
        delete pcampture;
    }

    if (pTex)
    {
        pTex->destroy();
        delete pTex;
        pTex = nullptr;
    }
}

void QOpenGLTest::InitShaders()
{
    bool bSucceed = false;
    bSucceed = shaderProgram.addShaderFromSourceCode(QOpenGLShader::Vertex, shaders::vertexShaderT);
    if (!bSucceed)
    {
        qDebug() << shaderProgram.log();
    }
    bSucceed = shaderProgram.addShaderFromSourceCode(QOpenGLShader::Fragment, shaders::fragmentShaderT);
    if (!bSucceed)
    {
        qDebug() << shaderProgram.log();
    }
    shaderProgram.link();
}

void QOpenGLTest::InitVertex()
{
    GLfloat vertices[] = {
        //Location         //Color          //texture 
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f, 1.0f,
        1.0f, -1.0f, 0.0f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 0.5f, 0.0f, 0.0f,0.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 0.2f, 0.2f, 0.2f, 0.0f, 1.0f,
    };

    QOpenGLVertexArrayObject::Binder vaoBind(&vao);

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, sizeof(GLfloat) * 4 * 8);

    //enable attr
    int attr = -1;
    attr = shaderProgram.attributeLocation("aPos");
    shaderProgram.setAttributeBuffer(attr, GL_FLOAT, 0, 3, sizeof(GLfloat) * 8);
    shaderProgram.enableAttributeArray(attr);

    attr = shaderProgram.attributeLocation("aColor");
    shaderProgram.setAttributeBuffer(attr, GL_FLOAT, sizeof(GLfloat) * 3, 3, sizeof(GLfloat) * 8);
    shaderProgram.enableAttributeArray(attr);

    attr = shaderProgram.attributeLocation("aTexture");
    shaderProgram.setAttributeBuffer(attr, GL_FLOAT, sizeof(GLfloat) * 6, 2, sizeof(GLfloat) * 8);
    shaderProgram.enableAttributeArray(attr);

    vbo.release();
}

void QOpenGLTest::LoadTexture(QVideoFrame& framData)
{
    if (pTex)
    {
        pTex->destroy();
        delete pTex;
        pTex = nullptr;
    }

    framData.map(QAbstractVideoBuffer::ReadOnly);
    int nbytes = framData.mappedBytes();
    //(framData.bits(), framData.width(), framData.height(), QVideoFrame::imageFormatFromPixelFormat(framData.pixelFormat()));
    //qDebug() << "frame data size :" << framData.mappedBytes();

    pTex = new QOpenGLTexture(QOpenGLTexture::Target::Target2D);
    mFrameSize = framData.size();
    pTex->setSize(width(), height());
    pTex->setFormat(QOpenGLTexture::RGBFormat);
    pTex->setWrapMode(QOpenGLTexture::ClampToEdge);
    pTex->setMinMagFilters(QOpenGLTexture::Linear, QOpenGLTexture::Linear);
    pTex->setWrapMode(QOpenGLTexture::Repeat);
    pTex->setData(QImage::fromData(framData.bits(), nbytes));
    pTex->allocateStorage();
    framData.unmap();
}

void QOpenGLTest::LoadTexture(QString strPicDir)
{
    if (pTex)
    {
        pTex->destroy();
        delete pTex;
        pTex = nullptr;
    }

    pTex = new QOpenGLTexture(QImage(strPicDir).mirrored());
    pTex->setMinificationFilter(QOpenGLTexture::Nearest);
    pTex->setMagnificationFilter(QOpenGLTexture::Linear);
    pTex->setWrapMode(QOpenGLTexture::Repeat);

}

void QOpenGLTest::InitCamera()
{
    QCameraViewfinderSettings viewfinderSettings;
    //viewfinderSettings.setPixelFormat(QVideoFrame::Format_RGB24);
    // viewfinderSettings.setResolution(1920, 1080);
    // mCamera = new QCamera;
    camera.setViewfinderSettings(viewfinderSettings);
    camera.setViewfinder(pcampture);
    camera.start();
}

void QOpenGLTest::UninitCamera()
{
    camera.stop();
}

void QOpenGLTest::initializeGL()
{
    this->initializeOpenGLFunctions();

    InitShaders();
    InitVertex();
    LoadTexture(R"(C:\Users\xiaohwa2\source\repos\ToolBox\QOpenGLTest\Resources\1423_7361.25.png)");
    InitCamera();

    connect(pcampture, &QtCameraCapture::frameAvailable, this, [this](QVideoFrame cloneFrame) {
        makeCurrent();
        this->LoadTexture(cloneFrame);
        this->paintGL();
        this->update();
        doneCurrent();
    });
}

void QOpenGLTest::resizeGL(int w, int h)
{
}
#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1
void QOpenGLTest::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, width() * devicePixelRatio(), height() * devicePixelRatio());
    shaderProgram.bind();
    {
        if (pTex)
        {
            shaderProgram.setUniformValue("ourTexture", 0);
            pTex->bind();
            QOpenGLVertexArrayObject::Binder vaoBind(&vao);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

            //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            pTex->release();
        }
    }
    shaderProgram.release();
}
