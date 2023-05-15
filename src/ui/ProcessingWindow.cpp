#include "ui/processingwindow.h"
#include "ui_processingwindow.h"

#include "VideoHandling/videoframe.h"

ProcessingWindow::ProcessingWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ProcessingWindow)
{
    std::cout << "asss2" << std::endl;
    ProcessPlayer = new ProcessingPlayer(this);
    QObject::connect(ProcessPlayer, SIGNAL(ToBeDisplayed(QImage)),
                     this, SLOT(updatePlayerUI(QImage)));

    ui->setupUi(this);
}

ProcessingWindow::~ProcessingWindow()
{
    delete ProcessPlayer;
    delete ui;
}

cv::Point2f ProcessingWindow::MapToImageCoords(QSize map_size, cv::Size image_size, QPointF src_coords)
{
    float xScale = static_cast<float>(image_size.width) / static_cast<float>(map_size.width());
    float yScale = static_cast<float>(image_size.height) / static_cast<float>(map_size.height());

    int x = static_cast<int>(xScale * src_coords.x());
    int y = static_cast<int>(yScale * src_coords.y());

    return cv::Point2f(x, y);
}

void ProcessingWindow::updatePlayerUI(QImage img)
{
    if (!img.isNull())
    {
        ui->lblFrame->setAlignment(Qt::AlignCenter);
        ui->lblFrame->setPixmap(QPixmap::fromImage(img).scaled(ui->lblFrame->size(),
                                                            Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}

void ProcessingWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open Video"), ".",
                                                    tr("Video Files (*.avi, *.mpg, *.mp4)"));
    if (!filename.isEmpty())
    {
        if (!ProcessPlayer->LoadVideo(filename.toStdString().data()))
        {
            QMessageBox msgBox;
            msgBox.setText("The selected video could not be opened!");
            msgBox.exec();
        }
    }
}

void ProcessingWindow::on_pushButton_2_clicked()
{
    if (ProcessPlayer->isStopped())
    {
        ProcessPlayer->Play();
        ui->pushButton_2->setText(tr("Stop"));
    }
    else
    {
        ProcessPlayer->Stop();
        ui->pushButton_2->setText(tr("Play"));
    }
}
