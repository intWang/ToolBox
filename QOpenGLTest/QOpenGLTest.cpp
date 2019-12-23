#include "QOpenGLTest.h"
#include "Shaders.h"
#include <QByteArray>
#include <QCameraInfo>
#include <QTransform>

#define MOD_3D
#define USE_CAMERA

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

void QOpenGLTest::InitShaders3D()
{
    bool bSucceed = false;
    bSucceed = shaderProgram.addShaderFromSourceCode(QOpenGLShader::Vertex, shaders::vertexShader3D);
    if (!bSucceed)
    {
        qDebug() << shaderProgram.log();
    }
    bSucceed = shaderProgram.addShaderFromSourceCode(QOpenGLShader::Fragment, shaders::fragmentShader3D);
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
        0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.5f, 0.0f, 0.0f,0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 0.2f, 0.2f, 0.2f, 0.0f, 1.0f,
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

void QOpenGLTest::InitVertex3D()
{
    glEnable(GL_DEPTH_TEST);

    GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    QOpenGLVertexArrayObject::Binder vaoBind(&vao);

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, sizeof(GLfloat) * 36 * 5);

    //enable attr
    int attr = -1;
    attr = shaderProgram.attributeLocation("aPos");
    shaderProgram.setAttributeBuffer(attr, GL_FLOAT, 0, 3, sizeof(GLfloat) * 5);
    shaderProgram.enableAttributeArray(attr);

    attr = shaderProgram.attributeLocation("aTexture");
    shaderProgram.setAttributeBuffer(attr, GL_FLOAT, sizeof(GLfloat) * 3, 2, sizeof(GLfloat) * 5);
    shaderProgram.enableAttributeArray(attr);

    vbo.release();
    mModel.rotate(-55, 1.0, 0.5, 0.0);
    mView.translate(0.0, 0.0, -3.0);
    //mView = CalcLookAtMatrix(mCurCamPos, { 0,0,0 }, { 0,1,0 });
    mProjection.perspective(45, width() / height(), 0.1, 100);

    Transform(mModel, "model");
    Transform(mView, "view");
    Transform(mProjection, "projection");
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

    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    foreach(const QCameraInfo &cameraInfo, cameras) {
        if (nullptr == m_pCamera)
        {
            m_pCamera = std::make_shared<QCamera>(cameraInfo);
        }
        qDebug() << cameraInfo.deviceName() << endl;
    }

    m_pCamera->setViewfinderSettings(viewfinderSettings);
    m_pCamera->setViewfinder(pcampture);
    m_pCamera->start();

//     camera.setViewfinderSettings(viewfinderSettings);
//     camera.setViewfinder(pcampture);
//     camera.start();
}

void QOpenGLTest::Transform(QMatrix4x4& mTrans, const char* szUniformName)
{
    if (nullptr == szUniformName)
    {
        return;
    }
    // if we want transform effect .we need bind shader program first 
    if (shaderProgram.bind())
    {
        //transform
        shaderProgram.setUniformValue(szUniformName, mTrans);
        shaderProgram.release();
    }
}

void QOpenGLTest::UninitCamera()
{
    if (m_pCamera)
    {
        m_pCamera->stop();
    }
}

void QOpenGLTest::PaintNormal()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (pTex)
    {
        shaderProgram.setUniformValue("ourTexture", 0);
        pTex->bind();
        QOpenGLVertexArrayObject::Binder vaoBind(&vao);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        pTex->release();
    }
}

void QOpenGLTest::Paint3D()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (pTex)
    {
        shaderProgram.setUniformValue("ourTexture", 0);
        pTex->bind();
        QOpenGLVertexArrayObject::Binder vaoBind(&vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        pTex->release();
    }
}

void QOpenGLTest::Paint3D_MultiCube()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (pTex)
    {
        shaderProgram.setUniformValue("ourTexture", 0);
        pTex->bind();
        QOpenGLVertexArrayObject::Binder vaoBind(&vao);

        QVector3D cubePositions[] = {
            {0.0f,  0.0f,  0.0f},
            {2.0f,  5.0f, -15.0f},
            {-1.5f, -2.2f, -2.5f},
            {-3.8f, -2.0f, -12.3f},
            {2.4f, -0.4f, -3.5f},
            {-1.7f,  3.0f, -7.5f},
            {1.3f, -2.0f, -2.5f},
            {1.5f,  2.0f, -2.5f},
            {1.5f,  0.2f, -1.5f},
            {-1.3f,  1.0f, -1.5f}
        };
        int i = 0;
        for (auto vec : cubePositions)
        {
            QMatrix4x4 model;
            model.translate(vec);
            int angle = (20 * i++ + (GetTickCount64() / 100)) % 360;
            model.rotate(angle, 1.0f, 0.3f, 0.5f);
            shaderProgram.setUniformValue("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        pTex->release();
    }
}

QMatrix4x4 QOpenGLTest::CalcLookAtMatrix(QVector3D position, QVector3D target, QVector3D worldUp)
{
    // 1. Position = known
    // 2. Calculate cameraDirection
    QVector3D zaxis = position - target;
    // 3. Get positive right axis vector
    QVector3D xaxis = QVector3D::crossProduct(worldUp, zaxis);
    // 4. Calculate camera up vector
    QVector3D yaxis = QVector3D::crossProduct(zaxis, xaxis);

    // Create translation and rotation matrix
    // In glm we access elements as mat[col][row] due to column-major layout
    QMatrix4x4 translation = {
        1,0,0,position.x() * -1,
        0,1,0,position.y() * -1,
        0,0,1,position.z() * -1,
        0,0,0,1
    };
    QMatrix4x4 rotation = {
        xaxis.x(), xaxis.y(), xaxis.z(), 0,
        yaxis.x(), yaxis.y(), yaxis.z(), 0,
        zaxis.x(), zaxis.y(), zaxis.z(), 0,
        0, 0, 0, 1,
    };

    // Return lookAt matrix as combination of translation and rotation matrix
    return rotation * translation; // Remember to read from right to left (first translation then rotation)
}

void QOpenGLTest::initializeGL()
{
    this->initializeOpenGLFunctions();
#ifdef MOD_3D
    InitShaders3D();
    InitVertex3D();
#else
    InitShaders();
    InitVertex();
#endif

#ifdef USE_CAMERA
    InitCamera();
    connect(pcampture, &QtCameraCapture::frameAvailable, this, [this](QVideoFrame cloneFrame) {
        makeCurrent();
        this->LoadTexture(cloneFrame);
        this->paintGL();
        this->update();
        doneCurrent();
    });
#else
    LoadTexture(R"(C:\Users\xiaohwa2\source\repos\ToolBox\QOpenGLTest\Resources\1423_7361.25.png)");
#endif
    
}

void QOpenGLTest::resizeGL(int w, int h)
{
}
#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1
void QOpenGLTest::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glViewport(0, 0, width() * devicePixelRatio(), height() * devicePixelRatio());
    shaderProgram.bind();
    {
#ifdef MOD_3D
        //Paint3D();
        Paint3D_MultiCube();
#else
        PaintNormal();
#endif
    }
    shaderProgram.release();
}

void QOpenGLTest::keyPressEvent(QKeyEvent *event)
{
    QVector3D camPos;

    switch (event->key())
    {
    case Qt::Key_Left:
        camPos = { 1,0,0 };
        break;
    case Qt::Key_Right:
        camPos = { -1,0,0 };
        break;
    case Qt::Key_Up:
        camPos = { 0,1,0 };
        break;
    case Qt::Key_Down:
        camPos = { 0,-1,0 };
        break;
    default:
        break;
    }
    mCurCamPos += camPos;
    mView = CalcLookAtMatrix(mCurCamPos, { 0,0,0 }, { 0,1,0 });
    Transform(mView, "view");
}

void QOpenGLTest::wheelEvent(QWheelEvent *event)
{
    QMatrix4x4 view;
    view.scale(event->delta()>0? 1.1:0.9);
    mView *= view;
    Transform(mView, "view");
}
