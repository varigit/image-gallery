#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    image = 0;

    QStringList filters;
    filters << "*.jpeg" << "*.jpg";

    imagesDir = new QDir ( "/usr/share/camera-images/");

    imagesDir->setFilter(QDir::Files);
    imagesDir->setNameFilters( filters);
    imagesDir->setSorting(QDir::Name);
    imagesList = imagesDir->entryList();


     ui->prevImage->hide();
    if(imagesList.count() == 0 || imagesList.count() == 1) {

        ui->nextImage->hide();

        if(imagesList.count() == 0) {
            ui->clearImages->hide();
        }
    }

    if(imagesList.count() > 0)
        displayImage(0);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_prevImage_clicked()
{
    currentIndex--;
    if(currentIndex <= 0)
       ui->prevImage->hide();

    if(currentIndex < imagesList.count())
       ui->nextImage->show();

    displayImage(currentIndex);
}

void MainWindow::on_clearImages_clicked()
{
     ui->nextImage->hide();
     ui->prevImage->hide();

     QStringList clearList = imagesDir->entryList();

     for(int x = 0; x < clearList.size() ; x++ ) {
         imagesDir->remove(clearList[x]);
     }

     ui->clearImages->hide();
    ui->label->hide();

}

void MainWindow::on_nextImage_clicked()
{
    currentIndex++;
    if(currentIndex >= 3)
       ui->nextImage->hide();

    ui->prevImage->show();

    displayImage(currentIndex);

}

void MainWindow::displayImage(int index) {


    if(image) {
        delete image;
    }

    image = new QPixmap("/usr/share/camera-images/"+imagesList[index]);

    ui->label->setPixmap(*image);

    QSize pixSize = image->size();
    pixSize.scale(size(), Qt::KeepAspectRatio);
    ui->label->setFixedSize(pixSize);
}
