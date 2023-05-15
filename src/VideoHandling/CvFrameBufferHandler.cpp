#include "VideoHandling/CvFrameBufferHandler.h"

CvFrameBufferHandler::CvFrameBufferHandler(const std::string& filename, bool outputVideo)
{
    _videoCap = new cv::VideoCapture(filename);
    if (!_videoCap->isOpened())
	{
		std::cerr << "Error: Could not open video file " << filename << std::endl;
        return;
	}
    _videoCap->read(_curr_rgb_frame);

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
    _prev_rgb_frame = _curr_rgb_frame.clone();
    return _videoCap->read(_curr_rgb_frame);
}

bool CvFrameBufferHandler::WriteFrame(cv::Mat &frame)
{
    if (!_writerCap->isOpened())
        return false;

    if (!frame.empty())
    {
        std::cout << "Writing processed frame" << std::endl;
        _writerCap->write(frame);
        return true;
    }
    else
    {
        std::cout << "Writing not-touched frame" << std::endl;
        _writerCap->write(_curr_rgb_frame);
        return true;
    }

}

cv::Mat* CvFrameBufferHandler::GetCurrRgbFrame()
{
    return &_curr_rgb_frame;
}

cv::Mat* CvFrameBufferHandler::GetPrevRgbFrame()
{
    return &_prev_rgb_frame;
}

int CvFrameBufferHandler::GetFramerate()
{
    return _videoCap->get(cv::CAP_PROP_FPS);
}

cv::Size CvFrameBufferHandler::GetFrameSize()
{
    return cv::Size(_videoCap->get(cv::CAP_PROP_FRAME_WIDTH), _videoCap->get(cv::CAP_PROP_FRAME_HEIGHT));
}

void CvFrameBufferHandler::initializeVideoWriter(const std::string &filename)
{
    std::string folderName = std::filesystem::path(filename).parent_path().string();
    std::string videoName = std::filesystem::path(filename).stem().string();
    std::string extension = std::filesystem::path(filename).extension().string();

    std::string outputFileName = folderName + "/output/" + videoName + "output" + extension; //"C:/Users/ass/Documents/qt-projects/CV-CS-graduateWork/output/12.mp4";//
    _writerCap = new cv::VideoWriter(outputFileName, cv::VideoWriter::fourcc('X', 'V', 'I', 'D'), GetFramerate(), GetFrameSize());

}
