#pragma once

#include <QObject>
#include <QAbstractVideoSurface>
#include <queue>

enum class VideoFormat
{
    UNKNOWN,
    RGB,
    BGR,
    BGR_Flip,
    I420,
    YUY2,
    VL_YUV, //Proprietary YUV format for the CPVE codec (ARM platform only)
};

struct VideoFrame
{
    VideoFormat format;
    uint32_t timestamp;
    size_t width;
    size_t height;

    //The offset of edges of the region of interest
    size_t top;
    size_t bottom;
    size_t left;
    size_t right;

    size_t size;
    void* data;

    void* rawFormat;
    int32_t rawType;
};

class QtCameraCapture : public QAbstractVideoSurface
{
    Q_OBJECT

public:
    QtCameraCapture(QObject *parent = nullptr);
    ~QtCameraCapture();

    virtual QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType type = QAbstractVideoBuffer::NoHandle) const override;

    virtual bool present(const QVideoFrame &frame) override;

    void pushQueue(VideoFrame frame)
    {
        mVideoFrame.push(frame);
    }

    VideoFrame popQueue()
    {
        if (mVideoFrame.size() > 0)
        {
            VideoFrame frame = mVideoFrame.front();
            mVideoFrame.pop();
            return frame;
        }
        else
        {
            VideoFrame tmpFrame;
            tmpFrame.width = 0;
            tmpFrame.height = 0;
            tmpFrame.size = 0;
            return  tmpFrame;
        }
    }
signals:
    void frameAvailable(QVideoFrame cloneFrame);

private:
    std::queue<VideoFrame> mVideoFrame;
};
