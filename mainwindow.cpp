/* 
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/ 
 * 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

QString dirLocation;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);


    currentIndex = 0;

    QStringList filters;
    filters << "*.jpeg" << "*.jpg";

    imagesDir = new QDir (dirLocation);

    imagesDir->setFilter(QDir::Files);
    imagesDir->setNameFilters( filters);
    imagesDir->setSorting(QDir::Name);
    imagesList = imagesDir->entryList();


     ui->prevImage->setEnabled(false);
    if(imagesList.count() == 0 || imagesList.count() == 1) {

        ui->nextImage->setEnabled(false);

        if(imagesList.count() == 0) {
            ui->label->clear();
            ui->label->setText("No images found");
            ui->clearImages->setEnabled(false);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_prevImage_clicked()
{
    currentIndex--;
    if(currentIndex <= 0)
       ui->prevImage->setEnabled(false);

    if(currentIndex < imagesList.count())
       ui->nextImage->setEnabled(true);

    displayImage(currentIndex);
}

void MainWindow::on_clearImages_clicked()
{

     QMessageBox::StandardButton reply;
     reply = QMessageBox::question(this,"Delete Confirmation","Delete image?",QMessageBox::Yes|QMessageBox::No);

     if(reply == QMessageBox::No)
         return;

     ui->nextImage->setEnabled(false);
     ui->prevImage->setEnabled(false);

     QStringList clearList = imagesDir->entryList();


    imagesDir->remove(clearList[currentIndex]);

    imagesDir->refresh();

    imagesList = imagesDir->entryList();

    currentIndex--;

    if(currentIndex < 0)
        currentIndex = 0;

    ui->nextImage->setEnabled(false);
    ui->prevImage->setEnabled(false);

    if(imagesList.count() > 1 && imagesList.count() -1 > currentIndex)
        ui->nextImage->setEnabled(true);

    if(currentIndex > 0)
        ui->prevImage->setEnabled(true);

    if(imagesList.count() >= 1)
        displayImage(currentIndex);
    else {
        ui->clearImages->setEnabled(false);
        ui->label->clear();
        ui->label->setText("No images found");
    }


}

void MainWindow::on_nextImage_clicked()
{
    currentIndex++;
    if(currentIndex >= imagesList.size()-1)
       ui->nextImage->setEnabled(false);

    ui->prevImage->setEnabled(true);

    displayImage(currentIndex);

}

void MainWindow::displayImage(int index) {

    int width = ui->label->width();
    int height = ui->label->height();
    QPixmap image;
    image.load(dirLocation+imagesList[index]);
    image = image.scaled(width,height,Qt::KeepAspectRatio);
    ui->label->setPixmap(image);

}

void MainWindow::on_pushButton_clicked()
{
    this->close();
}
void MainWindow::showEvent(QShowEvent *ev)
{
    QMainWindow::showEvent(ev);

    if(imagesList.count() > 0)
        displayImage(0);
}


