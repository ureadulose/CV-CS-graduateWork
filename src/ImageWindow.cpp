#include "ui/ImageWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    VTPlayer = new VideoTrackerPlayer();
    QObject::connect(VTPlayer, SIGNAL(ToBeDisplayed(QImage)),
                     this, SLOT(updatePlayerUI(QImage)));

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete VTPlayer;
    delete ui;
}

void MainWindow::updatePlayerUI(QImage img)
{
    if (!img.isNull())
    {
        ui->label->setAlignment(Qt::AlignCenter);
        ui->label->setPixmap(QPixmap::fromImage(img).scaled(ui->label->size(),
                                                            Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}

void MainWindow::on_pushButton_clicked()
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

void MainWindow::on_pushButton_2_clicked()
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

