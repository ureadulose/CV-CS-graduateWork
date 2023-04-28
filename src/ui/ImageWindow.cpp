#include "ui/imagewindow.h"
#include "ui_imagewindow.h"

#include "VideoHandling/videoframe.h"

ImageWindow::ImageWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageWindow)
{
    VTPlayer = new VideoTrackerPlayer();
    QObject::connect(VTPlayer, SIGNAL(ToBeDisplayed(QImage)),
                     this, SLOT(updatePlayerUI(QImage)));

    ui->setupUi(this);

    QObject::connect(ui->lblFrame, SIGNAL(MousePosSignal()),
                     this, SLOT(MouseCurrentPos()));
    QObject::connect(ui->lblFrame, SIGNAL(MousePressedSignal()),
                     this, SLOT(MousePressed()));
    QObject::connect(ui->lblFrame, SIGNAL(MouseLeftFrameSignal()),
                     this, SLOT(MouseLeftFrame()));

    // maybe one day ill change it to overriding resizeEvent() signal so the image would be resize while video is paused.
    ui->lblFrame->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
}

ImageWindow::~ImageWindow()
{
    delete VTPlayer;
    delete ui;
}

cv::Point2f ImageWindow::MapToImageCoords(QSize map_size, cv::Size image_size, QPointF src_coords)
{
    float xScale = static_cast<float>(image_size.width) / static_cast<float>(map_size.width());
    float yScale = static_cast<float>(image_size.height) / static_cast<float>(map_size.height());

    int x = static_cast<int>(xScale * src_coords.x());
    int y = static_cast<int>(yScale * src_coords.y());

    return cv::Point2f(x, y);
}

void ImageWindow::updatePlayerUI(QImage img)
{
    if (!img.isNull())
    {
        ui->lblFrame->setAlignment(Qt::AlignCenter);
        ui->lblFrame->setPixmap(QPixmap::fromImage(img).scaled(ui->lblFrame->width()-0.1, ui->lblFrame->height()-0.1/*ui->lblFrame->size()*/,
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

void ImageWindow::MouseCurrentPos()
{
    ui->lblMousePos->setText(QString("X = %1, Y = %2").arg(ui->lblFrame->GetCurrentMousePos().x()).arg(ui->lblFrame->GetCurrentMousePos().y()));
}

void ImageWindow::MousePressed()
{
    // calculating difference between pixmap size and lblFrame size (in which pixmap is drawn)
    QSize lbl_pixmap_diff = ui->lblFrame->size() - ui->lblFrame->pixmap().size();
    // calculating target point which is equal to (click coordinates - difference)
    QPointF target = QPointF(ui->lblFrame->GetCurrentMousePos().x() - lbl_pixmap_diff.width(), ui->lblFrame->GetCurrentMousePos().y() - lbl_pixmap_diff.height() / 2);
    // translating to framesize-based coordinates
    cv::Point2f obj_coords = MapToImageCoords(ui->lblFrame->pixmap().size(), VTPlayer->GetFrameSize(), target);

    VTPlayer->RefreshTrackCoords(obj_coords);
}

void ImageWindow::MouseLeftFrame()
{

}

