#include "VideoHandling/CvFrameBufferHandler.h"

CvFrameBufferHandler::CvFrameBufferHandler(const std::string& filename, bool outputVideo)
{
    _videoCap = new cv::VideoCapture(filename);
    if (!_videoCap->isOpened())
	{
		std::cerr << "Error: Could not open video file " << filename << std::endl;
        return;
	}
    _videoCap->read(_currRgbFrame);

    if (outputVideo)
        initializeVideoWriter(filename);
}

CvFrameBufferHandler::~CvFrameBufferHandler()
{
    if (_videoCap->isOpened())
    {
        _videoCap->release();
        delete _videoCap;
    }

    if (_writerCap->isOpened())
    {
        _writerCap->release();
        delete _writerCap;
    }
}

bool CvFrameBufferHandler::Exists()
{
    return _videoCap->isOpened();
}

bool CvFrameBufferHandler::ReadFrame()
{
    _prevRgbFrame = _currRgbFrame.clone();
    return _videoCap->read(_currRgbFrame);
}

bool CvFrameBufferHandler::WriteFrame(cv::Mat &frame)
{
    if (!_writerCap->isOpened())
        return false;

    if (frame.empty())
        return false;

    _writerCap->write(frame);
    return true;
}

cv::Mat* CvFrameBufferHandler::GetCurrRgbFrame()
{
    return &_currRgbFrame;
}

cv::Mat* CvFrameBufferHandler::GetPrevRgbFrame()
{
    return &_prevRgbFrame;
}

int CvFrameBufferHandler::GetFramerate()
{
    return _videoCap->get(cv::CAP_PROP_FPS);
}

cv::Size CvFrameBufferHandler::GetFrameSize()
{
    return cv::Size(_videoCap->get(cv::CAP_PROP_FRAME_WIDTH), _videoCap->get(cv::CAP_PROP_FRAME_HEIGHT));
}

int CvFrameBufferHandler::GetChannelsAmount()
{
    return _currRgbFrame.channels();
}

void CvFrameBufferHandler::initializeVideoWriter(const std::string &filename)
{
    std::string folderName = std::filesystem::path(filename).parent_path().string();
    std::string videoName = std::filesystem::path(filename).stem().string();
    std::string extension = std::filesystem::path(filename).extension().string();

    std::string outputFileName = folderName + "/output/" + videoName + "output" + ".avi"/*extension*/; //"C:/Users/ass/Documents/qt-projects/CV-CS-graduateWork/output/12.mp4";//
    _writerCap = new cv::VideoWriter(outputFileName, cv::VideoWriter::fourcc('D', 'I', 'V', 'X'), GetFramerate(), GetFrameSize());
}
