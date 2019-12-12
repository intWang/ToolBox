#include "QtCameraWnd.h"
#include <QtMultimedia/QCameraViewfinderSettings>
#include <QCameraInfo>
#include "LocalDefine.h"
#include <algorithm>
#include "Shaders.h"
QtCameraWnd::QtCameraWnd(QWidget *parent)
    :QtDrawWnd(parent)
{
    m_pCapture = new QtCameraCapture;
    connect(m_pCapture, &QtCameraCapture::frameAvailable, this, [this](VideoFrame cloneFrame) {
        makeCurrent();
        this->loadFrame(cloneFrame);
        this->paintGL();
        doneCurrent();
    });
}

QtCameraWnd::~QtCameraWnd()
{
}

bool QtCameraWnd::StartCamera()
{
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    foreach(const QCameraInfo &cameraInfo, cameras) {
        m_pCamera = std::make_shared<QCamera>(cameraInfo);
        break;
    }

    if (m_pCamera)
    {
        //init camera device
        QCameraViewfinderSettings viewfinderSettings;
        viewfinderSettings.setPixelFormat(QVideoFrame::Format_YUYV);
        // viewfinderSettings.setResolution(1920, 1080);
        // mCamera = new QCamera;
        m_pCamera->setViewfinderSettings(viewfinderSettings);
        m_pCamera->setViewfinder(m_pCapture);
        m_pCamera->start();
        return true;
    }
    
    return false;
}

bool QtCameraWnd::StopCamera()
{
    if (m_pCamera != NULL)
    {
        m_pCamera->stop();
        m_pCamera = nullptr;
    }
    return true;
}

void QtCameraWnd::initializeGL()
{
    this->initializeOpenGLFunctions();
    // create vertex shader
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_ALPHA_TEST);

    // initialize vertex shader
    QOpenGLShader* vShader = new QOpenGLShader(QOpenGLShader::Vertex);
    vShader->compileSourceCode(shaders::passThroughVertSrc);
    if (!vShader->isCompiled())
    {
        qDebug()<<vShader->log();
        // failed to compile vertex shader
    }

    // initialize fragment shader
    QOpenGLShader* fShader = new QOpenGLShader(QOpenGLShader::Fragment);
    fShader->compileSourceCode(shaders::yuv2rgbFragSrc);

    if (!fShader->isCompiled())
    {
        qDebug() << vShader->log();
        // failed to compile fragment shader
    }

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1

    // link program shaders
    shaderProgram.addShader(vShader);
    shaderProgram.addShader(fShader);
    shaderProgram.bindAttributeLocation("position", PROGRAM_VERTEX_ATTRIBUTE);
    shaderProgram.bindAttributeLocation("texturepos", PROGRAM_TEXCOORD_ATTRIBUTE);

    shaderProgram.link();
    if (!shaderProgram.isLinked())
    {
        // failed to link shaders
    }

    if (shaderProgram.bind())
    {
        mTextureUniformLocations[0] = shaderProgram.uniformLocation("ytexture");
        mTextureUniformLocations[1] = shaderProgram.uniformLocation("utexture");
        mTextureUniformLocations[2] = shaderProgram.uniformLocation("vtexture");

        shaderProgram.setUniformValue("ytexture", mTextureUniformLocations[0]);
        shaderProgram.setUniformValue("utexture", mTextureUniformLocations[1]);
        shaderProgram.setUniformValue("vtexture", mTextureUniformLocations[2]);

        QMatrix4x4 m;
        m.ortho(-1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f);

        QVector2D s(200, 200);

        shaderProgram.setUniformValue("matrix", m);
        shaderProgram.setUniformValue("texturesize", s);
    }

}

void QtCameraWnd::paintGL()
{
    if (!context())
    {
        //LOGINFO(std::string("VDIVideoWindow::paintGL() error, context() is nil."));
        return;
    }

    makeCurrent();

    // aspect ratios
    float currentViewAspect = height() != 0 ? (float)width() / (float)height() : 0;
    float currentVideoAspect = mFrameSize.height() != 0 ? (float)mFrameSize.width() / (float)mFrameSize.height() : 0;

    if (currentViewAspect != mViewAspect || currentVideoAspect != mVideoAspect)
    {
        mViewAspect = currentViewAspect;
        mVideoAspect = currentVideoAspect;

        updateVertexBuffer();
    }

    if (mScaleFactor > 1.0f)
    {
        const auto dpiWidth = width() * devicePixelRatio();
        const auto dpiHeight = height() * devicePixelRatio();

        const auto newWidth = dpiWidth * mScaleFactor;
        const auto newHeight = dpiHeight * mScaleFactor;

        auto widthDiff = (dpiWidth - newWidth) / 2;
        auto heightDiff = (dpiHeight - newHeight) / 2;

        //Clamp the borders so you cannot pan past the image
        int xPos = std::max(std::min(static_cast<int>(widthDiff + mDragOffset.x()), 0), static_cast<int>(dpiWidth - newWidth));
        int yPos = std::max(std::min(static_cast<int>(heightDiff - mDragOffset.y()), 0), static_cast<int>(dpiHeight - newHeight));

        glViewport(xPos, yPos, newWidth, newHeight);
    }
    else
    {
        glViewport(0, 0, width() * devicePixelRatio(), height() * devicePixelRatio());
    }

    glClearColor(mBackground.redF(), mBackground.greenF(), mBackground.blueF(), 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (shaderProgram.isLinked())
    {
        shaderProgram.enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
        shaderProgram.enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);

        if (vbo.bind())
        {
            shaderProgram.setAttributeBuffer(PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, 0, 3, 5 * sizeof(GLfloat));
            shaderProgram.setAttributeBuffer(PROGRAM_TEXCOORD_ATTRIBUTE, GL_FLOAT, 3 * sizeof(GLfloat), 2, 5 * sizeof(GLfloat));

            for (auto& pTextureUnit:mTextures)
            {
                if (pTextureUnit)
                {
                    pTextureUnit->bind();
                }
            }
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            for (auto& pTextureUnit : mTextures)
            {
                if (pTextureUnit)
                {
                    pTextureUnit->release();
                }
            }
            vbo.release();
        }
    }

    doneCurrent();
}

struct vertex
{
    GLfloat pos[3];
    GLfloat tex[2];

};
void QtCameraWnd::updateVertexBuffer()
{
    float verticalBorder = 0;
    float horizontalBorder = 0;

    if (mViewAspect > mVideoAspect) //window is wider
    {
        horizontalBorder = 1.0f - (mVideoAspect / mViewAspect);
    }
    else if (mVideoAspect > mViewAspect) //window is taller
    {
        verticalBorder = 1.0f - (mViewAspect / mVideoAspect);
    }

    // initialize vertex buffer
    vertex vertexArray[4] = {
        { { 1.0f - horizontalBorder, -1.0f + verticalBorder, 0.0f }, { 1.0f, 0.0f } },
        { { -1.0f + horizontalBorder, -1.0f + verticalBorder, 0.0f }, { 0.0f, 0.0f } },
        { { -1.0f + horizontalBorder, 1.0f - verticalBorder, 0.0f }, { 0.0f, 1.0f } },
        { { 1.0f - horizontalBorder, 1.0f - verticalBorder, 0.0f }, { 1.0f, 1.0f } }
    };

    if (!vbo.isCreated())
    {
        vbo.create();
    }

    vbo.bind();
    vbo.allocate(&vertexArray[0], 4 * 5 * sizeof(GLfloat));
}

bool QtCameraWnd::loadFrame(const VideoFrame& frame)
{
    destoryFrame();
    bool sizeChanged = false;
    if (mFrameSize.width() != frame.width || mFrameSize.height() != frame.height)
    {
        mFrameSize.setWidth((int)frame.width);
        mFrameSize.setHeight((int)frame.height);
        sizeChanged = true;
    }
    //alloca texture
    try
    {
        for (auto& pTextureUnit : mTextures)
        {
            pTextureUnit = new QOpenGLTexture(QOpenGLTexture::Target2D);
            pTextureUnit->setSize((int)frame.width, (int)frame.height);
            pTextureUnit->setFormat(QOpenGLTexture::LuminanceFormat);
            pTextureUnit->setWrapMode(QOpenGLTexture::ClampToEdge);
            pTextureUnit->setMinMagFilters(QOpenGLTexture::Linear, QOpenGLTexture::Linear);
            if (!pTextureUnit->create())
            {
                throw "Create Failed";
            }
        }
    }
    catch (...)
    {
        
    }
    //alloca texture-end
    //load data
    glActiveTexture(GL_TEXTURE0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    mTextures[0]->setData(0, 0, QOpenGLTexture::Luminance, QOpenGLTexture::UInt8, &((unsigned char*)frame.data)[0]);

    glActiveTexture(GL_TEXTURE1);
    int uoffset = ((int)frame.width * (int)frame.height);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    mTextures[1]->setData(0, 0, QOpenGLTexture::Luminance, QOpenGLTexture::UInt8, &((unsigned char*)frame.data)[uoffset]);

    glActiveTexture(GL_TEXTURE2);
    int voffset = uoffset + ((int)frame.width >> 1) * ((int)frame.height >> 1);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    mTextures[2]->setData(0, 0, QOpenGLTexture::Luminance, QOpenGLTexture::UInt8, &((unsigned char*)frame.data)[voffset]);
    //load data--end
    free(frame.data);
    return true;
}

void QtCameraWnd::destoryFrame()
{
    for (auto& pItem: mTextures)
    {
        if (pItem)
        {
            pItem->destroy();
            delete pItem;
            pItem = nullptr;
        }
    }
}
