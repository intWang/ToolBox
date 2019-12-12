#include "QtCameraCapture.h"

QtCameraCapture::QtCameraCapture(QObject *parent)
    : QAbstractVideoSurface(parent)
{
}

QtCameraCapture::~QtCameraCapture()
{
}

QList<QVideoFrame::PixelFormat> QtCameraCapture::supportedPixelFormats(QAbstractVideoBuffer::HandleType type /*= QAbstractVideoBuffer::NoHandle*/) const
{
    ///Q_UNUSED(handleType);
    return QList<QVideoFrame::PixelFormat>()
        << QVideoFrame::Format_ARGB32
        << QVideoFrame::Format_ARGB32_Premultiplied
        << QVideoFrame::Format_RGB32
        << QVideoFrame::Format_RGB24
        << QVideoFrame::Format_RGB565
        << QVideoFrame::Format_RGB555
        << QVideoFrame::Format_ARGB8565_Premultiplied
        << QVideoFrame::Format_BGRA32
        << QVideoFrame::Format_BGRA32_Premultiplied
        << QVideoFrame::Format_BGR32
        << QVideoFrame::Format_BGR24
        << QVideoFrame::Format_BGR565
        << QVideoFrame::Format_BGR555
        << QVideoFrame::Format_BGRA5658_Premultiplied
        << QVideoFrame::Format_AYUV444
        << QVideoFrame::Format_AYUV444_Premultiplied
        << QVideoFrame::Format_YUV444
        << QVideoFrame::Format_YUV420P
        << QVideoFrame::Format_YV12
        << QVideoFrame::Format_UYVY
        << QVideoFrame::Format_YUYV
        << QVideoFrame::Format_NV12
        << QVideoFrame::Format_NV21
        << QVideoFrame::Format_IMC1
        << QVideoFrame::Format_IMC2
        << QVideoFrame::Format_IMC3
        << QVideoFrame::Format_IMC4
        << QVideoFrame::Format_Y8
        << QVideoFrame::Format_Y16
        << QVideoFrame::Format_Jpeg
        << QVideoFrame::Format_CameraRaw
        << QVideoFrame::Format_AdobeDng;
}

int YUV422To420(const uchar yuv422[],  uchar yuv420[], int width, int height)
{

    int ynum = width * height;
    int i, j, k = 0;
    //得到Y分量  
    for (i = 0; i < ynum; i++) {
        yuv420[i] = yuv422[i * 2];
    }
    //得到U分量  
    for (i = 0; i < height; i++) {
        if ((i % 2) != 0)continue;
        for (j = 0; j < (width / 2); j++) {
            if ((4 * j + 1) > (2 * width))break;
            yuv420[ynum + k * 2 * width / 4 + j] = yuv422[i * 2 * width + 4 * j + 1];
        }
        k++;
    }
    k = 0;
    //得到V分量  
    for (i = 0; i < height; i++) {
        if ((i % 2) == 0)continue;
        for (j = 0; j < (width / 2); j++) {
            if ((4 * j + 3) > (2 * width))break;
            yuv420[ynum + ynum / 4 + k * 2 * width / 4 + j] = yuv422[i * 2 * width + 4 * j + 3];

        }
        k++;
    }


    return 1;
}
bool QtCameraCapture::present(const QVideoFrame &frame)
{
    if (frame.isValid())
    {
        QVideoFrame cloneFrame(frame);
        cloneFrame.map(QAbstractVideoBuffer::ReadOnly);

        VideoFrame vf;
        vf.format = VideoFormat::I420;
        vf.width = frame.width();
        vf.height = frame.height();
        vf.size = vf.width * vf.height * 3;
        vf.size /= 2;

        QSize nSize = frame.size();
        auto format = frame.pixelFormat();

        uchar* buffer = (uchar *)malloc(vf.width * vf.height * 3 / 2);
        //memcpy(buffer, frame.bits(), vf.size);

        //YUV422To420(frame.bits(), buffer, vf.width, vf.height);
        //LOGINFO(FUNC_NAME, __L(vf.width), __L(vf.height), __L(frame.bits()), __L(mVideoFrame.size()));
        vf.data = buffer;

        //pushQueue(vf);
        emit frameAvailable(vf);
        cloneFrame.unmap();

        return true;
    }
    return false;
}
