#include "ui/imagewindow.h"
#include "ui_imagewindow.h"

#include "VideoHandling/videoframe.h"

ImageWindow::ImageWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageWindow)
{
    VTPlayer = new VideoTrackerPlayer(this);
    QObject::connect(VTPlayer, SIGNAL(ToBeDisplayed(QImage)),
                     this, SLOT(updatePlayerUI(QImage)));

    ui->setupUi(this);
    QObject::connect(ui->playbackSlider, SIGNAL(valueChanged(int)), VTPlayer, SLOT(SetPosition(int)));

    QObject::connect(ui->lblFrame, SIGNAL(MousePosSignal()),
                     this, SLOT(MouseCurrentPos()));
    QObject::connect(ui->lblFrame, SIGNAL(MouseLeftButtonPressedSignal(EventType)),
                     this, SLOT(MousePressed(EventType)));
    QObject::connect(ui->lblFrame, SIGNAL(MouseRightButtonPressedSignal(EventType)),
                     this, SLOT(MousePressed(EventType)));
    QObject::connect(ui->lblFrame, SIGNAL(MouseLeftFrameSignal()),
                     this, SLOT(MouseLeftFrame()));

    // maybe one day ill change it to overriding resizeEvent() signal so the image would be resize while video is paused.
    ui->lblFrame->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
}

ImageWindow::~ImageWindow()
{
    StopThreadAndFinish();
    delete VTPlayer;
    delete ui;
}

cv::Point2f ImageWindow::QLabelToMatCoords(QSize qlabelSize, QSize mapSize, cv::Size image_size)
{
    QSize qlabelMapDiff = qlabelSize - mapSize;
    QPointF srcCoords = QPointF(ui->lblFrame->GetCurrentMousePos().x() - qlabelMapDiff.width() / 2, ui->lblFrame->GetCurrentMousePos().y() - qlabelMapDiff.height() / 2);

    float xScale = static_cast<float>(image_size.width) / static_cast<float>(mapSize.width());
    float yScale = static_cast<float>(image_size.height) / static_cast<float>(mapSize.height());

    int x = static_cast<int>(xScale * srcCoords.x());
    int y = static_cast<int>(yScale * srcCoords.y());

    return cv::Point2f(x, y);
}

void ImageWindow::StopThreadAndFinish()
{
    VTPlayer->Stop();

    VTPlayer->quit();

    if (VTPlayer->isRunning())
    {
        VTPlayer->wait();
    }
}

void ImageWindow::updatePlayerUI(QImage img)
{
    if (!img.isNull())
    {
        ui->lblFrame->setAlignment(Qt::AlignCenter);
        ui->lblFrame->setPixmap(QPixmap::fromImage(img).scaled(ui->lblFrame->width()-0.1, ui->lblFrame->height()-0.1,
                                                            Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}

void ImageWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open Video"), ".",
                                                    tr("Video Files (*.avi, *.mpg, *.mp4)"));
    if (!filename.isEmpty())
    {
        if (!VTPlayer->LoadVideo(filename.toStdString().data()))
        {
            QMessageBox msgBox;
            msgBox.setText("The selected video could not be opened!");
            msgBox.exec();
        }
    }
}

void ImageWindow::on_pushButton_2_clicked()
{
    if (VTPlayer->isStopped())
    {
        VTPlayer->Play();
        ui->pushButton_2->setText(tr("Stop"));
    }
    else
    {
        VTPlayer->Stop();
        ui->pushButton_2->setText(tr("Play"));
    }
}

void ImageWindow::on_pushButton_3_clicked()
{
    if (VTPlayer->isStopped())
    {
        QString filename = QFileDialog::getOpenFileName(this,
                                                        tr("Open Video"), ".");/*,
                                                        tr("Video Files (*.avi, *.mpg, *.mp4)"));*/
        if (!filename.isEmpty())
        {
            if (!VTPlayer->LoadOptflow(filename.toStdString().data()))
            {
                QMessageBox msgBox;
                msgBox.setText("ya kusok govna i ne mogu normalno rabotat. tebe stoilo vybrat ImGui :)"/*"The selected video could not be opened!"*/);
                msgBox.exec();
            }
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Stop and reload the video first!");
        msgBox.exec();
    }
}

void ImageWindow::MouseCurrentPos()
{
    ui->lblMousePos->setText(QString("X = %1, Y = %2").arg(ui->lblFrame->GetCurrentMousePos().x()).arg(ui->lblFrame->GetCurrentMousePos().y()));
    if (!VTPlayer->isStopped())
    {
        cv::Point2f objCoords = QLabelToMatCoords(ui->lblFrame->size(), ui->lblFrame->pixmap().size(), VTPlayer->GetFrameSize());
        emit NewMousePos(EventType::MouseMove, objCoords);
    }
}

void ImageWindow::MousePressed(EventType event)
{
    cv::Point2f objCoords = QLabelToMatCoords(ui->lblFrame->size(), ui->lblFrame->pixmap().size(), VTPlayer->GetFrameSize());

    switch(event)
    {
    case EventType::MouseLeftPressed:
    {
        emit NewClick(EventType::MouseLeftPressed, objCoords);
        break;
    }
    case EventType::MouseRightPressed:
    {
        emit NewClick(EventType::MouseRightPressed, objCoords);
        std::cout<<"Right click"<<std::endl;
        break;
    }
    }

}

void ImageWindow::MouseLeftFrame()
{

}

